/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stckpush.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 17:16:06 by tiboitel          #+#    #+#             */
/*   Updated: 2014/12/01 18:58:26 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int		ft_stckpush(t_stack **stack, void *content, size_t content_size)
{
	t_stckelement	*elem;

	if (!stack || !*stack)
		return (0);
	(*stack)->top++;
	if ((elem = (t_stckelement *)ft_memalloc(sizeof(t_stckelement))) == NULL)
		return (0);
	if (!content || !content_size)
	{
		elem->content = NULL;
		elem->content_size = 0;
	}
	else
	{
		if ((elem->content = ft_memalloc(content_size)) == NULL)
			return (0);
		ft_memcpy(elem->content, content, content_size);
		elem->content_size = content_size;
	}
	if (((*stack)->element[(*stack)->top] = elem) == NULL)
		return (0);
	return (1);
}
