/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 15:57:07 by tiboitel          #+#    #+#             */
/*   Updated: 2014/11/05 16:51:38 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*tmp;

	tmp = NULL;
	if (!s)
		return (NULL);
	while (*s != '\0')
	{
		if (*s == c)
			tmp = s;
		s++;
	}
	if (*s == '\0' && c != 0 && tmp == NULL)
		return (NULL);
	if (c == 0)
		return ((char *)s);
	return ((char *)tmp);
}
