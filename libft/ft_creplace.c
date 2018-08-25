/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_creplace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/14 19:59:31 by tiboitel          #+#    #+#             */
/*   Updated: 2015/02/14 20:00:48 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_creplace(char *str, char org, char rplc)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == org)
			str[i] = rplc;
	}
	return (str);
}
