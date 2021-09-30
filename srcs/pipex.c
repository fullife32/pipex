/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/30 18:45:50 by eassouli         ###   ########.fr       */
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

int	main(int ac, char **av, char **env)
{
	t_list	**first;
	t_list	*lst;
	t_pipex	pipex;

	init_check(ac, env);
	lst = NULL;
	first = &lst;
	pipex.path_tmp = NULL; //a free
	pipex.env_path = NULL;
	file_check(av[1], av[ac - 1], pipex.file_fd);
	if (create_list(ac, av, env, &lst, &pipex) == -1)
		return (free_pipex(first, &pipex, -1)); //free correctement
	if (lst->fail == 1)
		lst = lst->next;
	while (lst)
	{
		pipex.pid = fork(); //check unlink
		if (pipex.pid == -1)
			perror("fork");
		if (pipex.pid == 0)
			exec_cmd(env, lst, &pipex);
		else
		{
			close(lst->pipe_fd[OUT]);
			if (lst)
				lst = lst->next;
		}
	}
	free_pipex(first, &pipex, 0);
	return (0);
}
