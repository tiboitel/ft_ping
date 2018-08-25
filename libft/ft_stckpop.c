/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stckpop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/27 16:47:34 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/01 18:12:31 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_stckelement		*ft_stckpop(t_stack **stack)
{
	t_stckelement *elem;

	if (!stack || !*stack)
		return (NULL);
	elem = (*stack)->element[(*stack)->top];
	free((*stack)->element[(*stack)->top]);
	(*stack)->element[(*stack)->top] = NULL;
	(*stack)->top--;
	if (elem == NULL)
		return (NULL);
	return (elem);
}
