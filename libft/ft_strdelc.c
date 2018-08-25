/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdelc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/03 19:34:46 by tiboitel          #+#    #+#             */
/*   Updated: 2015/02/18 21:19:13 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	ft_strlenc(char *str, char c)
{
	int		i;
	int		length;

	length = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] != c)
			length++;
	}
	return (length);
}

char		*ft_strdelc(char *str, char c)
{
	char	*delc;
	int		i;
	int		length;

	length = ft_strlenc(str, c);
	i = -1;
	delc = NULL;
	if (!(delc = (char *)malloc(sizeof(char) * length + 1)))
		return (NULL);
	delc[length] = '\0';
	length = 0;
	while (str[++i])
	{
		if (str[i] != c)
		{
			delc[length] = str[i];
			length++;
		}
	}
	return (delc);
}
