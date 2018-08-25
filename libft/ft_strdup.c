/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/03 18:31:53 by tiboitel          #+#    #+#             */
/*   Updated: 2014/12/12 09:14:02 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(const char *src)
{
	char	*duplicata;
	int		length;

	length = 0;
	length = ft_strlen(src);
	duplicata = malloc(length + 1);
	return (duplicata ? ft_strcpy(duplicata, src) : NULL);
}
