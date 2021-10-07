/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:24:13 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/07 18:48:42 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_pipe(int pipefd[])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	return (0);
}

int	create_list(int ac, char **av, t_list **lst, t_pipex *pipex)
{
	int		arg;
	t_list	*list;

	if (split_env(pipex) == -1)
		return (-1);
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
			return (-1);
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

// t_list	*create_node(int arg, char **av, t_list *list, t_pipex *pipex)
// {
// 	t_list	*new;

// 	new = ft_lstnew(list);
// 	if (new == NULL)
// 		return (NULL);
// 	if (create_pipe(new->pipe_fd) == -1)
// 		return (NULL);
// 	if (arg == 2 && pipex->file_fd[IN] == -1)
// 		new->fail = 1;
// 	if (split_args(arg, av, new, pipex) == -1)
// 		return (NULL);
// 	return (new);
// }

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
