/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 19:39:08 by tiboitel          #+#    #+#             */
/*   Updated: 2015/03/02 19:19:57 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_atoi(const char *str)
{
	int		result;
	int		operator;

	result = 0;
	operator = 1;
	while (ft_iswhitespace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			operator = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + operator * (*str - '0');
		str++;
	}
	return (result);
}
