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

int	ping_loop(char *target, bool verbose)
{
	int					sockfd;
	int					sequence; 
	int					transmitted;
	int					received;
	int 				err;
	uint8_t				send_buf[sizeof(t_icmp_packet)];
	uint8_t				recv_buff[1024];
	struct timeval		send_time;
	struct timeval		recv_time;
	t_icmp_packet		*pkt;
	t_rtt_stats 		stats;
	struct addrinfo		hints;
	struct addrinfo 	*res;
	struct sockaddr_in	*addr;
	char				addr_str[INET_ADDRSTRLEN];


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
	/* sockfd = setup_raw_socket();
	if (sockfd < 0)
	{
		freeaddrinfo(res);
		return (1);
	}*/
	signal(SIGINT, sigint_handler);
	addr = (struct sockaddr_in *)res->ai_addr;
	inet_ntop(AF_INET, &addr->sin_addr, addr_str, sizeof(addr_str));
	printf("PING %s (%s) 56(84) bytes of data.\n", target, addr_str);
	while (!g_stop_requested)
	{
		printf("%d bytes from %s: icmp_seq=%d, ttl=64, time=%2.f ms\n", 0, "0.0.0.0", 0, 0.00);
		usleep(1000000);
	}
	(void)stats;
	(void)verbose;
	(void)send_buf;
	(void)recv_buff;
	(void)send_time;
	(void)recv_time;
	(void)pkt;
	// close(sockfd);
	freeaddrinfo(res);
	return (0);
}
