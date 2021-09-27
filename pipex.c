/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/27 16:37:00 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(int pipefd[])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
}

int	file_check(char *path, int std)
{
	int	fd;
	
	if (std == OUT)
		fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror(path);
		return (-1);
	}
	if (dup2(fd, std) == -1)
		perror("dup2"); // exit ?
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	char	*access_path;
	int		pipe_fd[2];
	int		file_fd[2];
	char	**argv_tab;
	char	**argv_tab2;
	int		pid;
	int		infile;
	int		outfile;
	int		nb;

	if (ac < 5)
	{
		write(1, "pipex: Not enough arguments\n", 28);
		return (-1);
	}
	if (env == NULL)
	{
		write(1, "pipex: No valid environment found\n", 34);
	}
	nb = 3;
	argv_tab = NULL;
	argv_tab2 = NULL;
	
	create_pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close (pipe_fd[0]);
		if (dup2(pipe_fd[1], 1) == -1)
			perror("dup2"); //exit ?
		file_fd[0] = file_check(av[1], 0); //ac - 1 pour le dernier file check
		if (file_fd[0] == -1)
			return (-1); //exit ?
		// write(1, "test", 4);
		argv_tab = ft_split(av[2], ' ');
		if (argv_tab == NULL)
			perror ("ft_split"); //free
		char	**env_tab;
		ft_strncmp()
		if (execve("/bin/cat", argv_tab, env) == -1)
			perror ("execve"); //free
		close (pipe_fd[1]);
		exit(0);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			close (pipe_fd[1]);
			nb++;
			if (dup2(pipe_fd[0], 0) == -1)
				perror("dup2"); //exit ?
			if (nb == ac - 1)
				file_fd[0] = file_check(av[4], 1); //ac - 1 pour le dernier file check
			if (file_fd[0] == -1)
				return (-1); //exit ?
			argv_tab2 = ft_split(av[3], ' ');
			if (argv_tab2 == NULL)
				perror ("ft_split"); //free
			if (execve("/bin/cat", argv_tab2, env) == -1)
				perror ("execve"); //free;
			close (pipe_fd[0]);
			exit(0);
		}
	}
	return (0);
}