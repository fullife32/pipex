/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:32:19 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/06 19:27:20 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_list(t_list **first)
{
	if (*first)
		ft_lstclear(first, del);
	first = NULL;
}

void	free_env(t_pipex *pipex)
{
	int	i;

	if (pipex->env_path)
	{
		i = 0;
		while (pipex->env_path[i])
		{
			free(pipex->env_path[i]);
			pipex->env_path[i] = NULL;
			i++;
		}
		free(pipex->env_path);
		pipex->env_path = NULL;
	}
}

void	free_path(t_pipex *pipex)
{
	if (pipex->path_tmp != NULL)
		free(pipex->path_tmp);
	pipex->path_tmp = NULL;
}

void	free_pipex(t_list **first, t_pipex *pipex)
{
	free_list(first);
	free_env(pipex);
	// free_path(pipex);
	close(pipex->file_fd[IN]);
	close(pipex->file_fd[OUT]);
}
