/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:21:49 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 21:24:03 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

static volatile sig_atomic_t	g_stop_requested = 0;

static void	handle_signal(int sig)
{
	(void)sig;
	g_stop_requested = 1;
}

static void	print_usage(const char *prog_name)
{
	fprintf(stderr, USAGE_FMT, prog_name);
}

static void	print_version(void)
{
	printf("%s version %s\n", APP_NAME, VERSION);
}

int	main(int argc, char **argv)
{
	bool		verbose;
	char		*target;
	int			ret;
	int			i;

	verbose = false;
	target = NULL;
	i = 1;
	while (i < argc)
	{
		// Replace strcmp call with ft_strcmp
		if (strcmp(argv[i], "-v") == 0)
		{
			verbose = true;
		}
		else if (strcmp(argv[i], "--version") == 0
			|| strcmp(argv[i], "-V") == 0)
		{
			print_version();
			return (EXIT_SUCCESS);
		}
		else if (argv[i][0] == '-')
		{
			print_usage(argv[0]);
			return (EXIT_FAILURE);
		}
		else
		{
			target = argv[i];
		}
		i++;
	}
	if (target == NULL)
	{
		print_usage(argv[0]);
		return (EXIT_FAILURE);
	}
	if (signal(SIGINT, handle_signal) == SIG_ERR)
	{
		perror("signal:");
		return (EXIT_FAILURE);
	}
	ret = 0;
	ret = ping_loop(target, verbose);
	if (ret != 0)
	{
		fprintf(stderr, "Ping failed with code %d\n", ret);
	}
	return ((ret == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}
