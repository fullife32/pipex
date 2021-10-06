/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 14:38:23 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/06 19:29:09 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	del(void **ptr)
{
	if (*ptr)
		free(*ptr);
	*ptr = NULL;
}

void	del_path(t_list *lst)
{
	if (lst->path)
		free(lst->path);
	lst->path = NULL;
}

void	del_args(t_list *lst)
{
	int	i;

	i = 0;
	while (lst->args[i])
	{
		free(lst->args[i]);
		lst->args[i] = NULL;
		i++;
	}
}

void	ft_lstdelone(t_list *lst, void (*del)(void **))
{
	if (!lst || !del)
		return ;
	del_path(lst);
	// del_args(lst);
	close(lst->pipe_fd[IN]);
	close(lst->pipe_fd[OUT]);
	free(lst);
}
