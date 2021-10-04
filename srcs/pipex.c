/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/04 16:50:01 by eassouli         ###   ########.fr       */
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

int	main(int ac, char **av, char **env) //erreur 22 127 waitpid
{
	t_list	**first;
	t_list	*lst;
	t_pipex	pipex;

	init_check(ac, env);
	lst = NULL;
	first = &lst;
	pipex.env = env;
	pipex.ret = 0;
	pipex.path_tmp = NULL; //a free
	pipex.env_path = NULL;
	file_check(av[1], av[ac - 1], pipex.file_fd);
	if (create_list(ac, av, &lst, &pipex) == -1)
	{
		free_pipex(first, &pipex); //free correctement
		return (-1);
	}
	if (lst->fail == 1)
	{
		close(lst->pipe_fd[OUT]);
		lst = lst->next;
	}
	while (lst)
	{
		lst->pid = fork(); //check unlink
		if (lst->pid == -1)
			perror("fork");
		else if (lst->pid == 0)
			exec_cmd(env, lst, &pipex);
		else
		{
			close(lst->pipe_fd[OUT]);
			if (lst)
				lst = lst->next;
		}
	}
	pipex.ret = return_value(lst);
	free_pipex(first, &pipex);
	return (pipex.ret);
}

int	return_value(t_list *lst)
{
	int stat_loc;

	while (lst)
	{
		stat_loc = 0;
		waitpid(lst->pid, &stat_loc, 0);
		lst = lst->next;
	}
	return (WIFEXITED(stat_loc));
}
