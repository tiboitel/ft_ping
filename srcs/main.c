/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 20:21:49 by tiboitel          #+#    #+#             */
/*   Updated: 2025/04/13 22:04:07 by tiboitel         ###   ########.fr       */
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
	t_env		env;
	char		*target;
	int			ret;
	int			i;

	env.verbose = false;
	env.numeric_only = false;
	env.ttl = 64;
	env.ttl_specified = 0;
	target = NULL;
	i = 1;
	while (i < argc)
	{
		// Replace strcmp call with ft_strcmp
		if (strcmp(argv[i], "-v") == 0)
		{
			env.verbose = true;
		}
		else if (strcmp(argv[i], "-6") == 0)
		{
			env.enabled_ipv6 = true;
			env.ttl = 1;
		}
		else if (strcmp(argv[i], "-n") == 0)
		{
			env.numeric_only = 1;
		}
		else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc)
		{
			env.ttl = atoi(argv[++i]);
			env.ttl_specified = 1;
			if (env.ttl < 1 || env.ttl > 255)
			{
				fprintf(stderr, "Invalid TTL value. Must be between 1 and 255.\n");
				return EXIT_FAILURE;
			}
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
		fprintf(stderr, "signal: %s", strerror(errno));
		return (EXIT_FAILURE);
	}
	ret = 0;
	ret = ping_loop(target, &env);
	return ((ret == 0) ? EXIT_SUCCESS : EXIT_FAILURE);
}
