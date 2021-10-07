/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:39:19 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/29 14:09:42 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*ft_lstnew(t_list *lst)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (new == NULL)
		return (NULL);
	if (lst)
		new->prev = lst;
	else
		new->prev = NULL;
	new->fail = 0;
	new->path = NULL;
	new->args = NULL;
	new->next = NULL;
	return (new);
}
