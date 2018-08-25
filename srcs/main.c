/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 18:26:35 by tiboitel          #+#    #+#             */
/*   Updated: 2018/08/25 18:44:40 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

static void	ft_usage(void)
{
	printf("usage: ping [-v] # verbose output [-h sweepincrsize] hostname\n");
}

int			main(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_usage();
		return (COMMAND_LINE_USAGE_ERROR);
	}
	(void)argc;
	(void)argv;
	return (SUCCESSFUL_TERMINATION);
}
