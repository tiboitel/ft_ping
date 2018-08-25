/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 21:45:04 by tiboitel          #+#    #+#             */
/*   Updated: 2014/11/11 02:17:07 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "libft.h"

static int	ft_parcer(char const *s, int c, int i)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	tablen(char const *s, int c)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != c && (!s[i + 1] || s[i + 1] == c))
			len++;
		i++;
	}
	return (len);
}

char		**ft_strsplit(char const *s, int c)
{
	int		start;
	int		i;
	int		len;
	char	**new;

	len = 0;
	i = 0;
	start = 0;
	if (!s)
		return (NULL);
	new = (char**)malloc(sizeof(char *) * (tablen(s, c) + 1));
	if (!new)
		return (NULL);
	while (i < tablen(s, c))
	{
		len += start;
		while (s[len] == c)
			len++;
		start = ft_parcer(s, c, len) - len;
		new[i] = ft_strsub((const char *)s, len, start);
		i++;
	}
	new[i] = 0;
	return (new);
}
