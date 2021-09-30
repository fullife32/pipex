/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:38:23 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/30 18:31:45 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	del(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void	ft_lstdelone(t_list *lst, void (*del)(void **))
{
	int	i;
	if (!lst || !del)
		return ;
	del((void **)&lst->path);
	i = 0;
	while (lst->args[i])
	{
		del((void **)lst->args[i]);
		i++;
	}
	free(lst);
}
