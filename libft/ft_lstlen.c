/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 11:45:42 by tiboitel          #+#    #+#             */
/*   Updated: 2014/12/12 20:26:39 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_lstlen(t_list **alst)
{
	size_t	len;
	t_list	*tmp;

	if (!alst || !*alst)
		return (0);
	len = 0;
	tmp = *alst;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
