/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/06 19:50:23 by eassouli         ###   ########.fr       */
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
	t_list	*first;
	t_list	*lst;
	t_pipex	pipex;

	init_check(ac, env);
	lst = NULL;
	pipex.env = env;
	pipex.ret = 0;
	pipex.path_tmp = NULL;
	pipex.env_path = NULL;
	file_check(av[1], av[ac - 1], pipex.file_fd);
	if (create_list(ac, av, &lst, &pipex) == -1)
	{
		first = lst;
		free_pipex(&first, &pipex);
		exit(EXIT_FAILURE);
	}
	first = lst;
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
			lst = lst->next;
		}
	}
	pipex.ret = return_value(&first, &pipex);
	free_pipex(&first, &pipex);
	dprintf(2, "test\n");
	return (pipex.ret);
}

int	return_value(t_list **first, t_pipex *pipex)
{
	int	stat_loc;
	int	stat_loc_tmp;
	t_list	*lst;

	(void)pipex;
	lst = *first;
	stat_loc = 0;
	stat_loc_tmp = 0;
	while (lst->next)
	{
		close(lst->pipe_fd[IN]);
		close(lst->pipe_fd[OUT]);
		lst = lst->next;
	}
	waitpid(lst->pid, &stat_loc, 0);
	lst = lst->prev;
	while (lst)
	{
		if (lst->fail != 1)
			waitpid(lst->pid, &stat_loc_tmp, 0);
		lst = lst->prev;
	}
	return (WEXITSTATUS(stat_loc));
}
