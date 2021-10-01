/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:32:19 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/01 17:52:33 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipex(t_list **first, t_pipex *pipex)
{
	int	i;
	
	if (*first)
		ft_lstclear(first, del);
	first = NULL;
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
	if (pipex->path_tmp == NULL)
		free(pipex->path_tmp);
	pipex->path_tmp = NULL;
	close(pipex->file_fd[IN]);
	close(pipex->file_fd[OUT]);
}
