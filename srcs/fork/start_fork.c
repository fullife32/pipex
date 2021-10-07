/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_fork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:28:45 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/07 18:49:26 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	start_fork(t_list *lst, t_pipex *pipex)
{
	if (lst->fail == 1)
	{
		close(lst->pipe_fd[OUT]);
		lst = lst->next;
	}
	while (lst)
	{
		lst->pid = fork(); //check unlink
		if (lst->pid == -1)
			perror("fork");
		else if (lst->pid == 0)
			exec_cmd(lst, pipex);
		else
		{
			close(lst->pipe_fd[OUT]);
			lst = lst->next;
		}
	}
}
