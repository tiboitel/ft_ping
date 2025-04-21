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
# include "ping.h"

# define DEFAULT_TTL 64
# define RECV_TIMEOUT_SEC 1
# define RECV_TIMEOUT_USEC 0

int	setup_raw_socket(t_env *env);
int	send_icmp_packet(t_env *env, const void *pkt, size_t len,
		void *dest);
int	receive_icmp_reply(int sockfd, uint8_t *buf, size_t buffer,
		struct sockaddr *src);
bool reverse_dns_lookup(struct sockaddr *addr, char *host, size_t host_len);

#endif
