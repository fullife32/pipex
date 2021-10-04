/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:38:04 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/04 17:06:01 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_lstclear(t_list **lst, void (*del)(void **))
{
	t_list	*list;

	if (!lst || !del)
		return ;
	list = *lst;
	while (list != NULL)
	{
		ft_lstdelone(list, del);
		list = list->next;
	}
	*lst = NULL;
}
