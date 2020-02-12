/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 11:11:50 by wpark             #+#    #+#             */
/*   Updated: 2019/10/11 11:11:51 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*))
{
	t_list	*new;
	t_list	*bef;
	t_list	*begin;

	bef = 0;
	if (lst && f)
	{
		begin = ft_lstnew(f(lst->content));
		bef = begin;
		lst = lst->next;
		while (lst)
		{
			new = ft_lstnew(f(lst->content));
			bef->next = new;
			bef = new;
			lst = lst->next;
		}
		return (begin);
	}
	else
		return (0);
}
