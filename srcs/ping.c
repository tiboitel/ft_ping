/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:21:34 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 22:20:06 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"
#include "icmp.h"
#include "socket.h"
#include "utils.h"

static volatile sig_atomic_t	g_stop_requested = 0;

static void sigint_handler(int sig)
{
	(void)sig;
	g_stop_requested = 1;
}

static void print_summary(const char *host, const t_rtt_stats *stats,
		int transmitted, int received)
{
	double	avg;
	double	mdev;

	avg = 0.00;
	mdev = 0.00;
	printf("\n--- %s ping statistics ---\n", host);
	printf("%d packets transmitted, %d received, %1.f%% packet loss, time %dms\n",
			transmitted, received, ((transmitted - received) * 100.0) / transmitted, (int)(stats->sum * 1000.0));
	if (stats->count > 0)
	{
		avg =  stats->sum / stats->count;
		mdev = sqrt((stats->sumsq / stats->count) - (avg * avg));
		printf("rtt min/avg/max/mdev = %.3f/%.3f/%.3f/%.3f ms\n",
				stats->min, avg, stats->max, mdev);
	}
}

static void	update_rtt_stats(t_rtt_stats *stats, double rtt)
{
	if (stats->count == 0 || rtt < stats->min)
		stats->min = rtt;
	if (rtt > stats->max)
		stats->max = rtt;
	stats->sum += rtt;
	stats->sumsq += rtt * rtt;
	stats->count++;
}

int	ping_loop(char *target, bool verbose)
{
	int					sockfd;
	int					sequence; 
	int					transmitted;
	int					received;
	int 				err;
	int					n;
	int					valid;
	uint8_t				send_buf[sizeof(t_icmp_packet)];
	uint8_t				recv_buf[1024];
	double				rtt;
	struct timeval		send_time;
	struct timeval		recv_time;
	t_icmp_packet		*pkt;
	t_rtt_stats 		stats;
	struct addrinfo		hints;
	struct addrinfo 	*res;
	struct sockaddr_in	*addr;
	char				addr_str[INET_ADDRSTRLEN];
	socklen_t			addrlen;
	struct sockaddr_in	reply_addr;
	char				reply_ip[INET_ADDRSTRLEN];


	sockfd = -1;
	sequence = 0;
	transmitted = 0;
	received = 0;
	res = NULL;
	bzero(&stats, sizeof(t_rtt_stats));
	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	err = getaddrinfo(target, NULL, &hints, &res);
	if (err != 0)
	{
		fprintf(stderr, "DNS resolution failed for %s: %s\n", target, gai_strerror(err));
		return (1);
	}
	sockfd = setup_raw_socket();
	if (sockfd < 0)
	{
		freeaddrinfo(res);
		return (1);
	}
	signal(SIGINT, sigint_handler);
	addr = (struct sockaddr_in *)res->ai_addr;
	inet_ntop(AF_INET, &addr->sin_addr, addr_str, sizeof(addr_str));
	printf("PING %s (%s) 56(84) bytes of data.\n", target, addr_str);
	while (!g_stop_requested)
	{
		pkt = (t_icmp_packet *)send_buf;
		create_icmp_packet(pkt, ++sequence);
		gettimeofday(&send_time, NULL);

		if (send_icmp_packet(sockfd, send_buf, sizeof(t_icmp_packet), res->ai_addr) < 0) {
			perror("sendto:");
			continue;
		}
		transmitted++;
		addrlen = sizeof(reply_addr);
		n = receive_icmp_reply(sockfd, recv_buf, sizeof(recv_buf), (struct sockaddr *)&reply_addr);
		gettimeofday(&recv_time, NULL);
		if (n < 0)
		{
			if (errno == EINTR)
			{
				break;
			}
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				fprintf(stderr, "Request timeout for icmp_seq %d\n", sequence);
				continue;
			}
			perror("recvfrom:");
			continue;
		}
		rtt = time_diff_ms(&send_time, &recv_time);
		valid = parse_icmp_packet(recv_buf, n, verbose);
		if (valid)
		{
			received++;
			update_rtt_stats(&stats, rtt);
			bzero(&reply_ip, INET_ADDRSTRLEN);	
			inet_ntop(AF_INET, &reply_addr.sin_addr, reply_ip, sizeof(reply_ip));
			printf("%d bytes from %s: icmp_req=%d, ttl=%d, time=%.2f ms\n", (int)(n - sizeof(struct iphdr)), reply_ip, sequence, ((struct iphdr *)recv_buf)->ttl, rtt);
		}
		usleep(1000000);
	}
	print_summary(target, &stats, transmitted, received);
	close(sockfd);
	freeaddrinfo(res);
	return (0);
}
