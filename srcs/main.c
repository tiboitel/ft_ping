/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:26:35 by tiboitel          #+#    #+#             */
/*   Updated: 2018/08/25 20:38:40 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

static void	usage(void)
{
	printf("usage: ping [-v] # verbose output [-h sweepincrsize] hostname\n");
}

int			main(int argc, char **argv)
{
	int		opt;

	if (argc < 2)
	{
		usage();
		return (COMMAND_LINE_USAGE_ERROR);
	}
	/*if (getuid() != 0)
	{
		printf("ping: operation not permitted.\n");
		return (-1); // Need to check unix return code.
	}*/
	opt = 0;
	opt = ft_getopt(argc, argv, "vh", &setopt_callback);
	if (opt < 0)
	{
		dprintf(2, "ping: illegal options -- %c\n", opt);
		usage();
		return (-1); // Need to check unix return code.
	}
	if (opt & OPTVERBOSE)
		printf("Log: Verbose mode is activated.\n");
	if (opt & OPTSWEEPINCR)
		printf("Log: Sweepincr is activated\n");
	// check if an options is checked use
	// opt & FLAG
	return (SUCCESSFULL_TERMINATION);
}
