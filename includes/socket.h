/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:33:26 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 22:11:41 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_H
# define SOCKET_H

# include <sys/socket.h>
# include <netinet/ip_icmp.h>
# include <stdio.h>
# include <errno.h>
# include <strings.h>
# include <unistd.h>

# define DEFAULT_TTL 64
# define RECV_TIMEOUT_SEC 1
# define RECV_TIMEOUT_USEC 0

int	setup_raw_socket(void);
int	send_icmp_packet(int sockfd, const void *pkt, size_t len,
		const struct sockaddr *dest);
int	receive_icmp_reply(int sockfd, uint8_t *buf, size_t buffer,
		struct sockaddr *src);

#endif
