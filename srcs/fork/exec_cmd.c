/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:47:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/07 19:16:29 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmd(t_list *lst, t_pipex *pipex)
{
	if (dup_stdin(lst, pipex) == -1)
		(EXIT_FAILURE);
	if (dup_stdout(lst, pipex) == -1)
		(EXIT_FAILURE);
	if (execve(lst->path, lst->args, pipex->env) == -1)
	{
		if (access(lst->path, X_OK) == -1)
		{
			perror("execve");
			if (lst->prev)
				close(lst->prev->pipe_fd[IN]);
			close(lst->pipe_fd[OUT]);
			exit(errno);
		}
		else
		{
			close(lst->pipe_fd[IN]);
			close(lst->pipe_fd[OUT]);
			while (lst->prev)
				lst = lst->prev;
			free_pipex(&lst, pipex);
			exit(127);
		}
	}
}


// void	exec_cmd(t_list *lst, t_pipex *pipex)
// {
// 	if (dup_stdin(lst, pipex) == -1)
// 		(EXIT_FAILURE);
// 	if (dup_stdout(lst, pipex) == -1)
// 		(EXIT_FAILURE);
// 	if (access(lst->path, X_OK) == 0)
// 	{
// 		if (execve(lst->path, lst->args, pipex->env) == -1)
// 		{
// 			perror("execve");
// 			if (lst->prev)
// 				close(lst->prev->pipe_fd[IN]);
// 			close(lst->pipe_fd[OUT]);
// 			exit(errno);
// 		}
// 	}
// 	else if (access(lst->path, X_OK) == -1)
// 	{
// 		exit(125);
// 	}
// 	else
// 	{
// 		close(lst->pipe_fd[IN]);
// 		close(lst->pipe_fd[OUT]);
// 		while (lst->prev)
// 			lst = lst->prev;
// 		free_pipex(&lst, pipex);
// 		exit(127);
// 	}
// }