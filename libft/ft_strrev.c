/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/09 21:36:50 by tiboitel          #+#    #+#             */
/*   Updated: 2014/11/14 04:33:57 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strrev(char *str)
{
	char	current;
	int		i;
	int		j;

	i = 0;
	if (!str || *str == '\0')
		return (NULL);
	j = ft_strlen(str) - 1;
	while (i < j)
	{
		current = str[i];
		str[i] = str[j];
		str[j] = current;
		i++;
		j--;
	}
	return (str);
}
