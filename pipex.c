/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/27 18:01:18 by eassouli         ###   ########.fr       */
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

void	file_check(char *path1, char *path2, int file_fd[2])
{
	file_fd[0] = open(path1, O_RDONLY);
	if (file_fd[0] == -1)
	{
		perror(path1);
		exit(EXIT_FAILURE);
	}
	file_fd[1] = open(path2, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (file_fd[1] == -1)
	{
		perror(path2);
		close(file_fd[0]);
		exit(EXIT_FAILURE);
	}
}

char	*access_path(char **env)
{
	while (env || ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (env == NULL)
	{
		write(1, "pipex : No path for command found\n", 34); // A changer
		return (NULL);
	}
}

int	main(int ac, char **av, char **env)
{
	char	*cmd_path;
	int		pipe_fd[2];
	int		file_fd[2];
	char	**argv_tab;
	char	**argv_tab2;
	int		pid;
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
	file_check(av[1], av[ac - 1], file_fd);
	// cmd_path = access_path(env);
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close(pipe_fd[IN]);
		if (dup2(file_fd[IN], IN) == -1)
			perror("dup2"); //exit ?
		if (dup2(pipe_fd[OUT], OUT) == -1)
			perror("dup2"); //exit ?
		argv_tab = ft_split(av[2], ' ');
		if (argv_tab == NULL)
			perror ("ft_split"); //free
		if (execve("/bin/cat", argv_tab, env) == -1)
			perror ("execve"); //free
		close(pipe_fd[OUT]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			close(pipe_fd[OUT]);
			if (dup2(pipe_fd[IN], IN) == -1)
				perror("dup2"); //exit ?
			if (dup2(file_fd[OUT], OUT) == -1)
				perror("dup2"); // exit ?
			argv_tab2 = ft_split(av[3], ' ');
			if (argv_tab2 == NULL)
				perror ("ft_split"); //free
			if (execve("/bin/cat", argv_tab2, env) == -1)
				perror ("execve"); //free;
			close(pipe_fd[IN]);
			exit(0);
		}
	}
	return (0);
}