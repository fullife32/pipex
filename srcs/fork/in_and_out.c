/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_and_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:20:07 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/07 18:52:43 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	dup_stdin(t_list *lst, t_pipex *pipex) //return -1 fail
{
	if (lst->prev == NULL)
	{
		if (dup2(pipex->file_fd[IN], IN) == -1)
			perror("dup2");
		close(lst->pipe_fd[IN]);
	}
	else if (lst->next == NULL)
	{
		if (dup2(lst->prev->pipe_fd[IN], IN) == -1)
			perror("dup2");
		close(lst->pipe_fd[OUT]);
	}
	else
	{
		if (dup2(lst->prev->pipe_fd[IN], IN) == -1)
			perror("dup2");
	}
	return (0);
}

int	dup_stdout(t_list *lst, t_pipex *pipex)
{
	if (lst->next == NULL)
	{
		if (dup2(pipex->file_fd[OUT], OUT) == -1)
			perror("dup2");
	}
	else
	{
		if (dup2(lst->pipe_fd[OUT], OUT) == -1)
			perror("dup2");
	}
	return (0);
}
