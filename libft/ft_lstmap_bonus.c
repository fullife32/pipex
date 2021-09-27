/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:39:04 by eassouli          #+#    #+#             */
/*   Updated: 2021/01/02 14:59:44 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*first;
	t_list	*list;

	if (!lst || !f)
		return (NULL);
	first = NULL;
	while (lst != NULL)
	{
		list = ft_lstnew(f(lst->content));
		if (list == NULL)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		ft_lstadd_back(&first, list);
		lst = lst->next;
	}
	return (first);
}
