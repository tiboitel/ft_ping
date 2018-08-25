/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/12 23:35:50 by tiboitel          #+#    #+#             */
/*   Updated: 2016/06/01 18:12:10 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (alst == NULL || *alst == NULL || !del)
		return ;
	tmp = *alst;
	while (tmp)
	{
		del(tmp->content, tmp->content_size);
		tmp2 = tmp;
		free(tmp2);
		tmp = tmp->next;
	}
	free(tmp);
	*alst = NULL;
}
