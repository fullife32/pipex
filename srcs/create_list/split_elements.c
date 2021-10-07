/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:18:33 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/07 19:04:21 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	split_env(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->env[i] && ft_strncmp(pipex->env[i], "PATH=", 5) != 0)
		i++;
	if (pipex->env[i] == NULL)
	{
		write(1, "pipex : No environment path found\n", 34);
		return (-1);
	}
	pipex->env_path = ft_split(pipex->env[i] + 5, ':');
	if (pipex->env_path == NULL)
		return (-1);
	return (0);
}

int	access_path(t_list *list, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->env_path[i] && list->path == NULL)
	{
		list->path = ft_strjoin(pipex->env_path[i], pipex->path_tmp);
		if (list->path == NULL)
			return (-1);
		if (access(list->path, X_OK) == -1)
		{
			free(list->path);
			list->path = NULL;
		}
		i++;
	}
	return (0);
}

int	split_args(int arg, char **av, t_list *list, t_pipex *pipex)
{
	list->args = ft_split(av[arg], ' ');
	if (list->args == NULL)
		return (-1);
	if (*list->args && **list->args != '/')
	{
		pipex->path_tmp = ft_strjoin("/", *list->args);
		if (pipex->path_tmp == NULL)
			return (-1);
		if (access_path(list, pipex) == -1)
			return (-1);
	}
	if (*list->args != NULL && list->path == NULL)
		list->path = ft_strdup(*list->args);
	else if (*list->args == NULL)
		list->path = ft_strdup(" ");
	if (list->path == NULL)
		return (-1);
	if (list->fail == 0 && (access(list->path, X_OK) == -1 || *list->args == NULL))
	{
		write(2, list->path, ft_strlen(list->path));
		write(2, ": command not found\n", 21);
	}
	if (pipex->path_tmp)
		free(pipex->path_tmp);
	pipex->path_tmp = NULL;
	return (0);
}
