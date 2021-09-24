/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/24 18:47:50 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void	create_pipe(int pipefd[])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(-1);
	}
}

int	file_check(char *path, int flag)
{
	int	fd;
	
	fd = open(path, flag);
	if (fd == -1)
	{
		write(1, "pipex: ", 7);
		perror(path);
		return (-1);
	}
	if (dup2(0, fd) == -1)
		perror("dup2");
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int	pipefd[2];
	int	filefd[2];
	int	pid;
	int	infile;
	int	outfile;

	if (ac < 5)
	{
		write(1, "pipex: Not enough arguments\n", 28);
		return (-1);
	}
	create_pipe(pipefd);
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		if (dup2(1, pipefd[1]) == -1)
			perror("dup2"); //exit ?
		filefd[0] = file_check(av[1], O_RDWR);
		if (filefd[0] == -1)
			return (-1); //exit ?
		printf("%s\n", av[2]);
		execve("/bin/cat", &av[2], env);
	}
	return (0);
}