/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:38:23 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/01 16:52:04 by eassouli         ###   ########.fr       */
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
	close(lst->pipe_fd[IN]);
	close(lst->pipe_fd[OUT]);
	free(lst);
}
