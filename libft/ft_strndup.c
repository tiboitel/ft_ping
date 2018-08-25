/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:31:53 by tiboitel          #+#    #+#             */
/*   Updated: 2017/06/19 19:22:22 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strndup(const char *src, size_t n)
{
	char	*duplicata;
	int		length;

	length = 0;
	duplicata = NULL;
	length = ft_strlen(src);
	if (!(duplicata = malloc(length + 1)))
		return (NULL);
	ft_strncpy(duplicata, src, n);
	return (duplicata);
}
