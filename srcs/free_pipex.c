/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:32:19 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/30 18:45:20 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	free_pipex(t_list **first, t_pipex *pipex, int error)
{
	if (*first)
		ft_lstclear(first, del);
	if (pipex->env_path)
	{
		while (*pipex->env_path)
		{
			free(*pipex->env_path);
			*pipex->env_path++ = NULL;
		}
		free(pipex->env_path);
		pipex->env_path = NULL;
	}
	if (pipex->path_tmp == NULL)
		free(pipex->path_tmp);
	pipex->path_tmp = NULL;
	return (error);
}