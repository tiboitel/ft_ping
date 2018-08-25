/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 21:40:47 by tiboitel          #+#    #+#             */
/*   Updated: 2014/11/09 21:49:39 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memalloc(size_t size)
{
	char	*area;

	area = (void *)malloc(sizeof(char) * size);
	if (area == NULL)
		return (NULL);
	area = ft_memset(area, 0, size);
	return ((void *)area);
}
