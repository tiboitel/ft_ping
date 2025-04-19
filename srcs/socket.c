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

# include "socket.h"

int	setup_raw_socket(int family)
{
	int				is_ipv6;
	int				sockfd;
	int 			ttl;
	struct timeval	timeout;

	sockfd = 0;
	is_ipv6 = (family == AF_INET6);
	if (is_ipv6 == 0)
		sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	else
		sockfd = socket(AF_INET6, SOCK_RAW, IPPROTO_ICMPV6);
	if (sockfd < 0)
	{
		perror("socket: ");
		return (-1);
	}
	// Set TTL.
	ttl = DEFAULT_TTL;
	if (is_ipv6)
	{
		if (setsockopt(sockfd, IPPROTO_IPV6, IPV6_UNICAST_HOPS, &ttl, sizeof(ttl)) < 0)
		{
			perror("setsockopt: IPV6_UNICAST_HOPS");
			close(sockfd);
			return (-1);
		}
	}
	else
	{
		if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
		{
			perror("setsockopt: IP_TTL");
			close(sockfd);
			return (-1);
		}
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

int send_icmp_packet(t_env *env, const void *packet, size_t packet_size, void *dest)
{
	ssize_t sent = -0;
	size_t dest_len = 0;

	if (env->enabled_ipv6)
		dest_len =	sizeof(struct sockaddr_in6); 
	else
		dest_len = sizeof(struct sockaddr_in);
	sent  = sendto(env->sockfd, packet, packet_size, 0, dest, dest_len);
	if (sent < 0 || (size_t)sent != packet_size)
	{
		perror("sendto:");
		return (-1);
	}
	return 0;
}

int	receive_icmp_reply(int sockfd, uint8_t *buf, size_t buffer_size,
		struct sockaddr *src)
{
	socklen_t				addrlen;
	struct sockaddr_storage	src_storage;
	ssize_t					n;


	addrlen = sizeof(struct sockaddr_storage);
	n = 0;
	n = recvfrom(sockfd, buf, buffer_size, 0, (struct sockaddr *)&src_storage, &addrlen);
	if (n < 0)
	{
		return (-1);
	}
	return (int)n;
}


