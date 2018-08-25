/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 02:10:17 by tiboitel          #+#    #+#             */
/*   Updated: 2014/11/14 01:59:32 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strmap(const char *s, char (*f)(char))
{
	size_t	i;
	size_t	length;
	char	*ret;

	if (!s || !f)
		return (NULL);
	i = 0;
	length = ft_strlen(s);
	if ((ret = (char *)malloc(sizeof(char) * (length + 1))) == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		ret[i] = f(s[i]);
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
