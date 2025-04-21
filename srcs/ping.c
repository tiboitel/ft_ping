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

static void		handle_signal(int sig)
{
	(void)sig;
	g_stop_requested = 1;
}

// IPv4 handlers
static void		prepare_packet_v4(void *buf, int seq, t_env *env)
{
	(void)env;
	create_icmp_packet((t_icmp_packet *)buf, seq);
}

int				parse_reply_v4(uint8_t *buf, int len, int verbose)
{
	return (parse_icmp_packet(buf, len, verbose));
}

static void 	extract_reply_ip_v4(struct sockaddr *addr, char *ip_str, size_t len)
{
	struct sockaddr_in	*src;

	src = NULL;
	src = (struct sockaddr_in *)addr;
	inet_ntop(AF_INET, &src->sin_addr, ip_str, len);
}

// IPv6 handlers
static void		prepare_packet_v6(void *buf, int seq, t_env *env)
{
	struct sockaddr_in6	*dst6;
	struct in6_addr		src;

	dst6 = NULL;
	dst6 = (struct sockaddr_in6 *)env->target->ai_addr;
	src = in6addr_any;
	create_icmpv6_packet((t_icmpv6_packet *)buf, seq, &src, &dst6->sin6_addr);

}

static int		parse_reply_v6(uint8_t *buf, int len, int verbose)
{
	return parse_icmpv6_packet(buf, len, verbose);
}

static void		extract_reply_ip_v6(struct sockaddr *addr, char *ip_str, size_t len)
{
	struct sockaddr_in6	*src;

	src = NULL;
	src = (struct sockaddr_in6 *)addr;
	inet_ntop(AF_INET6, &src->sin6_addr, ip_str, len);
}

// main logic loop
int				ping_loop(char *target, t_env *env)
{
	// Packet buffers
	uint8_t					send_buf[1024];
	uint8_t					recv_buf[1024];

	// Timing
	double					rtt;
	struct timeval			send_time;
	struct timeval			recv_time;
	t_rtt_stats 			stats;

	// Counters
	int						sequence; 
	int						transmitted;
	int						received;
	int						payload_len;

	// ICMP and reply
	char					reply_ip[INET6_ADDRSTRLEN];

	// State
	int 					err;
	int						n;
	int						valid;
	int						is_ipv6;
	bool					dns_resolved;

	// Environment
	struct addrinfo			*res;
	struct addrinfo			hints;
	struct sockaddr_in		*addr;
	struct sockaddr_storage	recv_addr;			
	struct sockaddr_in6		*addr6;
	char 					hostname[NI_MAXHOST];
	char					*display_name;
	t_ping_behavior			behavior;

	env->sockfd = -1;
	sequence = 0;
	transmitted = 0;
	received = 0;
	payload_len = 0;
	dns_resolved = false;
	res = NULL;
	bzero(&stats, sizeof(t_rtt_stats));
	bzero(&hints, sizeof(struct addrinfo));
	hints.ai_socktype = SOCK_RAW;
	if (env->enabled_ipv6)
	{
		hints.ai_family = AF_UNSPEC;
		hints.ai_protocol = 0;
	}
	else
	{
		hints.ai_family = AF_INET;
		hints.ai_protocol = IPPROTO_ICMP;
	}
	err = getaddrinfo(target, NULL, &hints, &res);
	is_ipv6 = (res->ai_family == AF_INET6);
	is_ipv6 = env->enabled_ipv6 && is_ipv6; 
	if (is_ipv6)
	{
		behavior = (t_ping_behavior) {
			.prepare_packet = prepare_packet_v6,
				.send_packet = send_icmp_packet,
				.recv_packet = receive_icmp_reply,
				.parse_reply = parse_reply_v6,
				.extract_reply_ip = extract_reply_ip_v6,
				.packet_size = sizeof(t_icmpv6_packet)
		};
	}
	else
	{

		behavior = (t_ping_behavior) {
			.prepare_packet = prepare_packet_v4,
				.send_packet = send_icmp_packet,
				.recv_packet = receive_icmp_reply,
				.parse_reply = parse_reply_v4,
				.extract_reply_ip = extract_reply_ip_v4,
				.packet_size = sizeof(t_icmp_packet)
		};
	}

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
	signal(SIGINT, handle_signal);
	addr = (struct sockaddr_in *)res->ai_addr;
	if (is_ipv6)
	{
		addr6 = (struct sockaddr_in6 *)res->ai_addr;
		inet_ntop(env->family, &addr6->sin6_addr, env->target_ip, sizeof(env->target_ip));
	}
	else
	{
		inet_ntop(env->family, &addr->sin_addr, env->target_ip, sizeof(env->target_ip));
	}
	printf("PING %s (%s) 56(84) bytes of data.\n", target, env->target_ip);
	while (!g_stop_requested)
	{
		++sequence;
		behavior.prepare_packet(send_buf, sequence, env);
		gettimeofday(&send_time, NULL);
		if (behavior.send_packet(env, send_buf, behavior.packet_size, res->ai_addr)  < 0) {
			transmitted++;
			sleep(1);
			continue;
		}
		n = behavior.recv_packet(env->sockfd, recv_buf, sizeof(recv_buf), (struct sockaddr *)&recv_addr);
		gettimeofday(&recv_time, NULL);
		if (n < 0)
		{
			if (errno == EINTR)
				break;
			if (errno == EAGAIN || errno == EWOULDBLOCK)
			{
				fprintf(stderr, "Request timeout for icmp_seq %d\n", sequence);
				continue;
			}
			perror("recvfrom:");
			continue;
		}
		rtt = time_diff_ms(&send_time, &recv_time);
		valid = behavior.parse_reply(recv_buf, n, env->verbose);
		if (valid)
		{
			received++;
			update_rtt_stats(&stats, rtt);
			behavior.extract_reply_ip((struct sockaddr *)&recv_addr, reply_ip, sizeof(reply_ip));
			dns_resolved = reverse_dns_lookup((struct sockaddr *)&recv_addr, hostname, sizeof(hostname));
			display_name = (dns_resolved) ? hostname : reply_ip;
			payload_len = n - (is_ipv6 ? 0 : sizeof(struct iphdr));
			if (env->numeric_only)
			{
				printf("%d bytes from %s: icmp_req=%d, ttl=%d, time=%.2f ms\n", 
						payload_len,
						reply_ip,
						sequence, 
						((struct iphdr *)recv_buf)->ttl,
						rtt);

			}
			else
			{
				printf("%d bytes from %s (%s): icmp_req=%d, ttl=%d, time=%.2f ms\n", 
						payload_len,
						display_name,
						reply_ip,
						sequence, 
						((struct iphdr *)recv_buf)->ttl,
						rtt);
			}
		}
		transmitted++;
		usleep(1000000);
	}
	print_summary(target, &stats, transmitted, received);
	close(env->sockfd);
	freeaddrinfo(res);
	return (0);
}
