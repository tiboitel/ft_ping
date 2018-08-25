/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 21:43:49 by tiboitel          #+#    #+#             */
/*   Updated: 2014/11/14 05:28:50 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	if (s2 == NULL || *s2 == '\0')
		return ((char *)s1);
	if (s1 == NULL || *s1 == '\0')
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		if ((unsigned char)s1[i] == (unsigned char)s2[0])
		{
			j = 1;
			while (((unsigned char)s1[i + j] == (unsigned char)s2[j])
					&& (i + j) < n)
				j++;
			if (!s2[j])
				return (&(((char *)s1))[i]);
		}
		i++;
	}
	return (NULL);
}
