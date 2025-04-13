/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:28:11 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 21:19:08 by tiboitel         ###   ########.fr       */
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
# define USAGE_FMT "Usage: %s [-v] <destination>\n"

typedef struct s_rtt_stats {
	double	min;
	double	max;
	double	sum;
	double	sumsq;
	int		count;
}		t_rtt_stats;

int	ping_loop(char *target, bool verbose);

#endif
