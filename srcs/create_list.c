/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:24:13 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/04 18:32:38 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	split_env(t_pipex *pipex)
{
	while (*pipex->env && ft_strncmp(*pipex->env, "PATH=", 5) != 0)
		pipex->env++;
	if (*pipex->env == NULL)
	{
		write(1, "pipex : No path for command found\n", 34); // A changer
		return (-1);
	}
	pipex->env_path = ft_split(*pipex->env + 5, ':');
	if (pipex->env_path == NULL)
		return (-1); // exit
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
	list->args = ft_split(av[arg], ' '); //si pas d'arg fix pipe marche quand meme
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
		list->path = ft_strdup(*list->args); //strdup, check quand meme access quand exec commande au cas ou ne marche pas
	else if (*list->args == NULL)
		list->path = ft_strdup(" ");
	if (list->path == NULL)
		return (-1);
	if (access(list->path, X_OK) == -1 || *list->args == '\0')
	{
		write(2, list->path, ft_strlen(list->path));
		write(2, ": command not found\n", 21);
	}
	if (pipex->path_tmp != NULL)
		free(pipex->path_tmp);
	pipex->path_tmp = NULL;
	return (0);
}

t_list	*create_node(int arg, char **av, t_list *list, t_pipex *pipex)
{
	t_list	*new;

	new = ft_lstnew(list);
	if (new == NULL)
		return (NULL);
	if (create_pipe(new->pipe_fd) == -1)
		return (NULL);
	if (arg == 2 && pipex->file_fd[IN] == -1)
		new->fail = 1;
	if (split_args(arg, av, new, pipex) == -1)
		return (NULL);
	return (new);
}

// int	create_list(int ac, char **av, t_list **lst, t_pipex *pipex)
// {
// 	int		arg;
// 	t_list	*list;

// 	if (split_env(pipex) == -1)
// 		return (-1);
// 	if (pipex->env_path == NULL)
// 		return (-1);
// 	arg = 2;
// 	*lst = create_node(arg, av, NULL, pipex);
// 	if (*lst == NULL)
// 		return (-1);
// 	list = *lst;
// 	list = list->next;
// 	arg++;
// 	while (arg < ac - 1)
// 	{
// 		list = create_node(arg, av, list, pipex);
// 		if (list == NULL)
// 			return (-1);
// 		list = list->next;
// 		arg++;
// 	}
// 	return (0);
// }


int	create_list(int ac, char **av, t_list **lst, t_pipex *pipex)
{
	int		arg;
	t_list	*list;

	if (split_env(pipex) == -1)
		return (-1); //free a la fin
	if (pipex->env_path == NULL)
		return (-1);
	arg = 2;
	list = NULL;
	while (arg < ac - 1)
	{
		if (list == NULL)
		{
			*lst = ft_lstnew(NULL);
			list = *lst;
		}
		else
		{
			list->next = ft_lstnew(list);
			list = list->next;
		}
		if (list == NULL)
			return (-1); //clear lst
		if (create_pipe(list->pipe_fd) == -1)
			return (-1);
		if (arg == 2 && pipex->file_fd[IN] == -1)
			list->fail = 1;
		if (split_args(arg, av, list, pipex) == -1)
			return (-1);
		arg++;
	}
	return (0);
}

// dprintf(2, "pipefd : %d %d list->path ; %s list-> argv[0] %s\n", list->pipe_fd[0], list->pipe_fd[1], list->path, list->args[0]);

