/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:33:26 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 21:18:10 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_H
# define SOCKET_H

# include <sys/socket.h>
# include <netinet/ip_icmp.h>

int	setup_raw_socket(void);
int	send_icmp_packet(int sockfd, const void *pkt, size_t len,
		const struct sockaddr *dest);
int	receive_imcp_reply(int sockfd, uint8_t *buf, size_t buffer,
		struct sockaddr *src);

#endif
