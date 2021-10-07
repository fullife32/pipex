/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:13:29 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/07 19:50:44 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	return_value(t_list **first)
{
	int		last_status;
	int		status;
	t_list	*lst;

	lst = *first;
	last_status = 0;
	status = 0;
	while (lst->next)
	{
		close(lst->pipe_fd[IN]);
		close(lst->pipe_fd[OUT]);
		lst = lst->next;
	}
	waitpid(lst->pid, &last_status, 0);
	close(lst->pipe_fd[IN]);
	close(lst->pipe_fd[OUT]);
	lst = lst->prev;
	while (lst)
	{
		if (lst->fail != 1)
			waitpid(lst->pid, &status, 0);
		lst = lst->prev;
	}
	return (WEXITSTATUS(last_status));
}
