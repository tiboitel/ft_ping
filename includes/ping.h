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
# include <math.h>
# include <errno.h>

# define APP_NAME "ft_ping"
# define VERSION "1.0"
# define USAGE_FMT "Usage: %s [-v] <destination>\n"

typedef struct s_env
{
	struct addrinfo	*target;
	char			target_ip[INET6_ADDRSTRLEN];
	int				family;
	int				sockfd;
	int				ttl;
	int				count;
	int				verbose;
	int				enabled_ipv6;
}				t_env;

typedef struct s_rtt_stats {
	double	min;
	double	max;
	double	sum;
	double	sumsq;
	int		count;
}		t_rtt_stats;

int	ping_loop(char *target, t_env *env);

#endif
