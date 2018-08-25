/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getopt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/25 19:49:46 by tiboitel          #+#    #+#             */
/*   Updated: 2018/08/25 20:38:34 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ping.h"

static int		isopt(const char *s)
{
	if (s[0] == '-' && (s[1] != '-' || s[1] != '\0' || s[1] != ' '))
		return (1);
	return (0);
}

void			setopt_callback(int flag, int *opt)
{
	if (flag == 118)
		*opt |= OPTVERBOSE;
	else if (flag == 104)
		*opt |= OPTSWEEPINCR;
}

int				ft_getopt(int argc, char **argv, const char *optstring, void (*setopt)(int flag, int *opt))
{
	size_t			i;
	size_t			j;
	size_t			k;
	int				opt;

	i = 0;
	opt = 0;
	if (argc == 1 || optstring == NULL)
		return (0);
	while (++i < (size_t)argc && isopt(argv[i]))
	{
		j = -1;
		k = 1;
		while (optstring[++j] != '\0')
		{
			if (argv[i][k] == optstring[j])
			{
				(*setopt)(argv[i][k], &opt);
				j = -1;
				k++;
			}
			if (ft_strchr(optstring, argv[i][k]) == NULL)
				return (-(argv[i][k]));
		}
	}
	return (opt);
}
