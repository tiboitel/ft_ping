/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:33:27 by tiboitel          #+#    #+#             */
/*   Updated: 2018/08/25 20:37:44 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <signal.h>
#include "libft.h"

# define DEFDATALEN 56
# define MAXWAIT 10000
# define MAXALARM (60 * 60)
# define MAXTOS 255
# define COMMAND_LINE_USAGE_ERROR 64
# define SUCCESSFULL_TERMINATION 0
# define OPTVERBOSE 2
# define OPTSWEEPINCR 4

/**
 * pr_packer()
 * pr_init()
 **/
void	setopt_callback(int flag, int *opt);
int		ft_getopt(int argc, char **argv, const char *optstring, void (*setopt)(int flag, int *opt));

#endif
