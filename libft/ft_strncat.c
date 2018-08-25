/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 17:25:31 by tiboitel          #+#    #+#             */
/*   Updated: 2014/11/14 05:27:48 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!dest || !src)
		return (0);
	if (!n)
		return (dest);
	i = ft_strlen(dest);
	while (src[j] != '\0' && n-- > 0)
	{
		dest[i++] = src[j++];
	}
	dest[i] = '\0';
	return (dest);
}
