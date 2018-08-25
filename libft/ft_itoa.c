/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 19:18:49 by tiboitel          #+#    #+#             */
/*   Updated: 2017/08/31 15:50:09 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char		*ft_itoa(int n)
{
	size_t	length;
	char	*a;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	length = ft_intlen(n);
	if ((a = ft_strnew(length + 1 + ((n < 0) ? 1 : 0))) == NULL)
		return (NULL);
	if (n < 0)
	{
		a[0] = '-';
		n = -n;
	}
	else
		length--;
	while (n > 9)
	{
		a[length--] = '0' + n % 10;
		n = n / 10;
	}
	if (n >= 0)
	{
		a[length] = '0' + n;
	}
	return (a);
}

char		*ft_utoa(unsigned int n)
{
	size_t	length;
	char	*a;

	length = ft_intlen(n);
	if ((a = ft_strnew(length + 1)) == NULL)
		return (NULL);
	else
		length--;
	while (n > 9)
	{
		a[length--] = '0' + n % 10;
		n = n / 10;
	}
	a[length] = '0' + n;
	return (a);
}
