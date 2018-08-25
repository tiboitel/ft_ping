/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiboitel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/09 10:36:42 by tiboitel          #+#    #+#             */
/*   Updated: 2015/02/18 21:19:32 by tiboitel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list		*ft_lstsortmerge(t_list *a, t_list *b,
		int (*f)(t_list *, t_list *))
{
	t_list	*newlst;

	newlst = NULL;
	if (!a)
		return (b);
	if (!b)
		return (a);
	if (f(a, b) <= 0)
	{
		newlst = a;
		newlst->next = ft_lstsortmerge(a->next, b, f);
	}
	else
	{
		newlst = b;
		newlst->next = ft_lstsortmerge(a, b->next, f);
	}
	return (newlst);
}

static void			ft_lstsplit(t_list *src, t_list **front, t_list **back)
{
	t_list	*slow;
	t_list	*fast;

	if (src == NULL || src->next == NULL)
	{
		*front = src;
		back = NULL;
	}
	else
	{
		slow = src;
		fast = src->next;
		while (fast)
		{
			fast = fast->next;
			if (fast != NULL)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = src;
		*back = slow->next;
		slow->next = NULL;
	}
}

int					ft_lstsort(t_list **alst, int (*f)(t_list *, t_list *))
{
	t_list		*head;
	t_list		*strong;
	t_list		*weak;

	if (!alst || !*alst)
		return (-1);
	head = *alst;
	if (!head || head->next == NULL)
		return (-1);
	ft_lstsplit(head, &strong, &weak);
	ft_lstsort(&strong, f);
	ft_lstsort(&weak, f);
	head = ft_lstsortmerge(strong, weak, f);
	*alst = head;
	return (1);
}
