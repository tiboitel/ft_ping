/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/10 04:00:26 by tiboitel          #+#    #+#             */
/*   Updated: 2014/11/12 21:11:49 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim(const char *s)
{
	char	*ret;
	size_t	len;

	if (!s)
		return (NULL);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	len = ft_strlen(s);
	while ((len-- > 0) && (s[len] == ' ' || s[len] == '\t' || s[len] == '\n'))
		;
	ret = ft_strsub(s, 0, len + 1);
	return ((ret == NULL) ? (NULL) : (ret));
}
