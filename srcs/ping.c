/* ************************************************************************** */
/*                                                                            */
 /*                                                                    :::::   */
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

int	ping_loop(char *target, t_env *env)
{
	int					sequence; 
	int					transmitted;
	int					received;
	int 				err;
	int					n;
	int					valid;
	int					is_ipv6;
	uint8_t				send_buf[1024];
	uint8_t				recv_buf[1024];
	double				rtt;
	struct timeval		send_time;
	struct timeval		recv_time;
	t_icmp_packet		*pkt4;
	t_icmpv6_packet		pkt6;
	t_rtt_stats 		stats;
	struct addrinfo		*res;
	struct addrinfo		hints;
	struct sockaddr_in	*addr;
	char			addr_str[INET_ADDRSTRLEN];
	struct sockaddr_storage	recv_addr;			
	socklen_t		addrlen;
	struct sockaddr_in6	dst6;
	char				reply_ip[INET_ADDRSTRLEN];

	env->sockfd = -1;
	sequence = 0;
	transmitted = 0;
	received = 0;
	res = NULL;
	bzero(&stats, sizeof(t_rtt_stats));
	bzero(&hints, sizeof(struct addrinfo));
	addrlen = sizeof(recv_addr);
	(void)addrlen;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;
	err = getaddrinfo(target, NULL, &hints, &res);
	is_ipv6 = (res->ai_family == AF_INET6);
	is_ipv6 = env->enabled_ipv6 && is_ipv6; 
	env->target = res;
	env->family = res->ai_family;
	if (err != 0)
	{
		fprintf(stderr, "DNS resolution failed for %s: %s\n", target, gai_strerror(err));
		return (1);
	}
	env->sockfd = setup_raw_socket(env->family);
	if (env->sockfd < 0)
	{
		freeaddrinfo(res);
		return (1);
	}
	signal(SIGINT, sigint_handler);
	addr = (struct sockaddr_in *)res->ai_addr;
	if (is_ipv6)
	{
		struct sockaddr_in6	*addr6 = (struct sockaddr_in6 *)res->ai_addr;
		inet_ntop(env->family, &addr6->sin6_addr, env->target_ip, sizeof(env->target_ip));
		printf("PING %s (%s) 56(84) bytes of data.\n", target, env->target_ip);
	}
	else
	{
		inet_ntop(env->family, &addr->sin_addr, env->target_ip, sizeof(env->target_ip));
		printf("PING %s (%s) 56(84) bytes of data.\n", target, addr_str);
	}
	while (!g_stop_requested)
	{
		void *dest = NULL;
		if (is_ipv6)
		{
			struct in6_addr src_addr;
			src_addr = in6addr_any;
			dst6 = *(struct sockaddr_in6 *)env->target->ai_addr;
			create_icmpv6_packet(&pkt6, ++sequence, &src_addr, &dst6.sin6_addr);
			memcpy(send_buf, &pkt6, sizeof(pkt6));
			dest = (void *)&dst6;
		}
		else
		{

			pkt4 = (t_icmp_packet *)send_buf;
			create_icmp_packet(pkt4, ++sequence);
			dest = (void *)res->ai_addr;
	
		}
		gettimeofday(&send_time, NULL);
		if (send_icmp_packet(env, send_buf, (is_ipv6) ? sizeof(t_icmpv6_packet) : sizeof(t_icmp_packet), dest)  < 0) {
			perror("sendto:");
			continue;
		}
		transmitted++;

		// receive reply
		n = receive_icmp_reply(env->sockfd, recv_buf, sizeof(recv_buf), (struct sockaddr *)&recv_addr);
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
		valid = (is_ipv6)
			? parse_icmpv6_packet(recv_buf, n, env->verbose)
			: parse_icmp_packet(recv_buf, n, env->verbose);
		if (valid)
		{
			received++;
			update_rtt_stats(&stats, rtt);
			bzero(&reply_ip, INET_ADDRSTRLEN);	

			if (is_ipv6)
			{
				struct sockaddr_in6	*src6 = (struct sockaddr_in6 *)&recv_addr;
				inet_ntop(AF_INET6, &src6->sin6_addr, reply_ip, sizeof(reply_ip));
				printf("%d bytes from %s: icmp_req=%d, time=%.2f ms\n",
						n, reply_ip, sequence, rtt);
			}
			else
			{
				struct sockaddr_in 	*src4 = (struct sockaddr_in *)&recv_addr;
				inet_ntop(AF_INET, &src4->sin_addr, reply_ip, sizeof(reply_ip));
				printf("%d bytes from %s: icmp_req=%d, ttl=%d, time=%.2f ms\n", (int)(n - sizeof(struct iphdr)), reply_ip, sequence, ((struct iphdr *)recv_buf)->ttl, rtt);
		
			}
		}
		usleep(1000000);
	}
	// cleanup 
	print_summary(target, &stats, transmitted, received);
	close(env->sockfd);
	freeaddrinfo(res);
	return (0);
}
