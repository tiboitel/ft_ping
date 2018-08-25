/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 03:26:25 by tiboitel          #+#    #+#             */
/*   Updated: 2015/02/18 21:14:53 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void	freejoin(char *s1, char *s2, int flag)
{
	if (flag == 3)
	{
		free(s1);
		s1 = NULL;
		free(s2);
		s2 = NULL;
	}
	if (flag == 2)
		free(s2);
	s2 = NULL;
	if (flag == 1)
	{
		free(s1);
		s1 = NULL;
	}
}

char		*ft_strfjoin(char *s1, char *s2, int flag)
{
	char	*ret;
	size_t	length;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	i = 0;
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	length = (ft_strlen(s1) + ft_strlen(s2));
	if ((ret = (char *)malloc(sizeof(char) * length + 1)) == NULL)
		return (NULL);
	while (*s1)
		ret[i++] = *s1++;
	while (*s2)
		ret[i++] = *s2++;
	ret[i] = '\0';
	freejoin(s1, s2, flag);
	return (ret);
}
