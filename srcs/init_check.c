/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 16:22:52 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/01 16:38:29 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_check(int ac, char **env)
{
	if (ac < 5)
	{
		write(1, "pipex: Not enough arguments\n", 28);
		exit(EXIT_FAILURE);
	}
	if (env == NULL)
	{
		write(1, "pipex: No valid environment found\n", 34);
		exit(EXIT_FAILURE);
	}
}

void	file_check(char *path1, char *path2, int file_fd[2])
{
	file_fd[0] = open(path1, O_RDONLY);
	if (file_fd[0] == -1)
		perror(path1);
	file_fd[1] = open(path2, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file_fd[1] == -1)
	{
		perror(path2);
		close(file_fd[0]);
		exit(1);
	}
}
