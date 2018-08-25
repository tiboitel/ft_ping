/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpushback.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/28 19:50:54 by tiboitel          #+#    #+#             */
/*   Updated: 2014/12/12 17:19:55 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstpushback(t_list **alst, t_list *new)
{
	t_list	*tmp;

	if (!new)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		(*alst)->next = NULL;
		return ;
	}
	tmp = *alst;
	if (tmp->next == NULL)
		(*alst)->next = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	tmp = NULL;
}
