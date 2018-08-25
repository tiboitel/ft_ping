/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 21:48:29 by tiboitel          #+#    #+#             */
/*   Updated: 2014/12/29 17:16:33 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;

	lst = NULL;
	if ((lst = (t_list *)ft_memalloc(sizeof(t_list))) == NULL)
		return (NULL);
	lst->next = NULL;
	if (!content || !content_size)
	{
		lst->content = NULL;
		content_size = 0;
	}
	else
	{
		if ((lst->content = ft_memalloc(content_size)) == NULL)
			return (NULL);
		ft_memcpy(lst->content, content, content_size);
		lst->content_size = content_size;
	}
	lst->next = NULL;
	return (lst);
}
