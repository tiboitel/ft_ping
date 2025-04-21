/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:11 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 21:49:39 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PING_H
# define PING_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <string.h>
# include <stdbool.h>
# include <netdb.h>
# include <sys/time.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <errno.h>

# define APP_NAME "ft_ping"
# define VERSION "1.0"
# define USAGE_FMT "Usage: %s [-vt6n] [-t ttl] destination\n"

typedef struct s_env
{
	struct addrinfo	*target;
	char			target_ip[INET6_ADDRSTRLEN];
	int				family;
	int				sockfd;
	int				ttl;
	int				ttl_specified;
	int				count;
	int				verbose;
	int				enabled_ipv6;
	int				numeric_only;
}				t_env;

typedef struct	s_ping_behavior {
	void	(*prepare_packet)(void *packet_buf, int seq, t_env *env);
	int		(*send_packet)(t_env *env, const void *packet_buf, size_t len, void *dest);
	int		(*recv_packet)(int sockfd, uint8_t *recv_buf, size_t buflen,
				struct sockaddr *recv_addr);
	int		(*parse_reply)(uint8_t *buf, int len, int verbose);
	void 	(*extract_reply_ip)(struct sockaddr *addr, char *ip_str, size_t len);
	size_t	packet_size;
}				t_ping_behavior;

int	ping_loop(char *target, t_env *env);

#endif
