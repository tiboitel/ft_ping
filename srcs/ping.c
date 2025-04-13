/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:21:34 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 21:27:07 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"
#include "icmp.h"
#include "socket.h"
#include "utils.h"

static void sigint_handler(int sig)
{
	(void)sig;
}

int	ping_loop(char *target, bool verbose)
{
	int					sockfd;
	int					sequence; 
	int					transmitted;
	int					received;
	int 				err;
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
	// /!\ Not implemented yet:
	// sockfd = setup_raw_socket();
	// if (sockfd < 0)
	// {
	// 	freeadrrinfo(res);
	// 	return (1);
	// }
	signal(SIGINT, sigint_handler);
	addr = (struct sockaddr_in *)res->ai_addr;
	inet_ntop(AF_INET, &addr->sin_addr, addr_str, sizeof(addr_str));
	printf("PING %s (%s) 56(84) bytes of data.\n", target, addr_str);
	(void)stats;
	(void)verbose;
	// /!\ Not implemented yet.
	// close(sockfd);
	freeaddrinfo(res);
	return (0);
}
