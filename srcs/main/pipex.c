/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/14 14:37:28 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **env)
{
	t_list	*first;
	t_list	*lst;
	t_pipex	pipex;

	init_check(ac, env);
	lst = NULL;
	init_values(env, &pipex);
	file_check(av[1], av[ac - 1], pipex.file_fd);
	if (create_list(ac, av, &lst, &pipex) == -1)
	{
		first = lst;
		free_pipex(&first, &pipex);
		exit(EXIT_FAILURE);
	}
	first = lst;
	start_fork(lst, &pipex);
	pipex.ret = return_value(&first);
	free_pipex(&first, &pipex);
	return (pipex.ret);
}
