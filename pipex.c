/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/27 15:19:46 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_pipe(int pipefd[])
{
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(-1);
	}
}

int	file_check(char *path, int flag, int std)
{
	int	fd;
	
	fd = open(path, flag);
	if (fd == -1)
	{
		write(1, "pipex: ", 7);
		perror(path);
		return (-1);
	}
	if (dup2(fd, std) == -1)
		perror("dup2"); // exit ?
	return (fd);
}

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	int		file_fd[2];
	char	**argv_tab;
	int		pid;
	int		infile;
	int		outfile;
	int		nb;

	if (ac < 5)
	{
		write(1, "pipex: Not enough arguments\n", 28);
		return (-1);
	}
	nb = 3;
	argv_tab = NULL;
	create_pipe(pipe_fd);
	pid = fork();
	if (pid == -1)
		perror("fork");
	if (pid == 0)
	{
		close (pipe_fd[0]);
		if (dup2(pipe_fd[1], 1) == -1)
			perror("dup2"); //exit ?
		file_fd[0] = file_check(av[1], O_RDONLY, 0); //ac - 1 pour le dernier file check
		if (file_fd[0] == -1)
			return (-1); //exit ?
		// write(1, "test", 4);
		argv_tab = ft_split(av[2], ' ');
		if (argv_tab == NULL)
			perror ("ft_split"); //free
		if (execve("/bin/cat", argv_tab, env) == -1)
			perror ("execve"); //free
		close (pipe_fd[1]);
	}
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			nb++;
			printf("%d", nb);
			close(pipe_fd[1]);
			if (dup2(pipe_fd[0], 0) == -1)
				perror("dup2"); //exit ?
			if (nb == ac - 1)
				file_fd[0] = file_check(av[1], O_WRONLY, 1); //ac - 1 pour le dernier file check
			if (file_fd[0] == -1)
				return (-1); //exit ?
			argv_tab = ft_split(av[3], ' ');
			if (argv_tab == NULL)
				perror ("ft_split"); //free
			if (execve("/bin/cat", argv_tab, env) == -1)
				perror ("execve"); //free;
			close (pipe_fd[0]);
		}
		else
		{
			write(1, "fini", 4);
		}
		
	}
	return (0);
}