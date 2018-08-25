/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stcknew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/26 21:40:25 by tiboitel          #+#    #+#             */
/*   Updated: 2015/02/18 21:15:56 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_stack	*ft_stcknew(size_t size_max)
{
	t_stack		*newstack;

	if (!size_max)
		return (NULL);
	if ((newstack = (t_stack *)ft_memalloc(sizeof(t_stack))) == NULL)
		return (NULL);
	newstack->element = (t_stckelement **)ft_memalloc(sizeof(t_stckelement) * \
			size_max);
	if (newstack->element == NULL)
		return (NULL);
	newstack->top = -1;
	return (newstack);
}
