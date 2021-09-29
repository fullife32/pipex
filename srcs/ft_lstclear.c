/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:38:04 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/28 11:57:14 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*nxt;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list != NULL)
	{
		nxt = list->next;
		ft_lstdelone(list, del);
		list = nxt;
	}
	*lst = NULL;
}