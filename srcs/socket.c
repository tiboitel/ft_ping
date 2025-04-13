/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 21:34:07 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 22:16:56 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "socket.h"

int	setup_raw_socket(void)
{
	int				sockfd;
	int 			ttl;
	struct timeval	timeout;

	sockfd = 0;
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		perror("socket: ");
		return (-1);
	}
	// Set TTL.
	ttl = DEFAULT_TTL;
	if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
	{
		perror("setsockopt: IP_TTL");
		close(sockfd);
		return (-1);
	}
	bzero(&timeout, sizeof(struct timeval));
	timeout.tv_sec = RECV_TIMEOUT_SEC;
	timeout.tv_usec = RECV_TIMEOUT_USEC;
	if (setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0)
	{
		perror("setsockopt: SO_RCVTIMEO");
		close(sockfd);
		return (-1);
	}

	return (sockfd);
}

int send_icmp_packet(int sockfd, const void *packet, size_t packet_size, const struct sockaddr *dest)
{
	(void)sockfd;
	(void)packet;
	(void)packet_size;
	(void)dest;
	return (0);
}

int	receive_imcp_reply(int sockfd, uint8_t *buf, size_t buffer,
		struct sockaddr *src)
{
	(void)sockfd;
	(void)buf;
	(void)buffer;
	(void)src;
	return (0);
}


