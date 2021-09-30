/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 17:26:30 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/30 17:38:19 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	dup_stdin(t_list *lst, t_pipex *pipex)
{
	if (lst->prev == NULL) //si premier IN
	{
		if (dup2(pipex->file_fd[IN], IN) == -1)
			perror("dup2"); //exit ?
		close(lst->pipe_fd[IN]);
	}
	else if (lst->next == NULL) //si dernier IN
	{
		if (dup2(lst->prev->pipe_fd[IN], IN) == -1)
			perror("dup2"); //exit ?
		close(lst->pipe_fd[OUT]);
	}
	else //milieu IN
	{
		if (dup2(lst->prev->pipe_fd[IN], IN) == -1)
			perror("dup2"); //exit ?
	}
	return (0);
}

int	dup_stdout(t_list *lst, t_pipex *pipex)
{
	if (lst->next == NULL) //si dernier OUT
	{
		if (dup2(pipex->file_fd[OUT], OUT) == -1)
			perror("dup2"); // exit ?
	}
	else // premier et milieu OUT
	{
		if (dup2(lst->pipe_fd[OUT], OUT) == -1)
			perror("dup2"); // exit ?
	}
	return (0);
}

void	exec_cmd(char **env, t_list *lst, t_pipex *pipex)
{
	if (dup_stdin(lst, pipex) == -1)
		(EXIT_FAILURE);
	if (dup_stdout(lst, pipex) == -1)
		(EXIT_FAILURE);
	if (access(lst->path, X_OK) == 0)
	{
		if (execve(lst->path, lst->args, env) == -1) //erreur si fichier1 non ouvert
			perror ("execve"); //free;
	}
	else
	{
		write(2, lst->path, ft_strlen(lst->path));
		write(2, ": command not found\n", 21);
		close(lst->pipe_fd[IN]);
		close(lst->pipe_fd[OUT]);
		exit(EXIT_FAILURE);
	}
}