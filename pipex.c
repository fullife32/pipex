/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/28 15:21:09 by eassouli         ###   ########.fr       */
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

t_list	*access_path(int ac, char **av, char **env, t_list **lst)
{
	char	**split_path;
	char	**split_args;
	int		arg;
	int		i;
	t_list	*list;

	split_path = NULL;
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (*env == NULL)
	{
		write(1, "pipex : No path for command found\n", 34); // A changer
		return (NULL);
	}
	split_path = ft_split(*env, ':');
	if (split_path == NULL)
		return (NULL); // exit
	arg = 2;
	*split_path += 5;
	list = NULL;
	while (arg < ac - 1)
	{
		if (list)
		{
			list->next = ft_lstnew(NULL);
			list = list->next;
		}
		else
		{
			*lst = ft_lstnew(NULL);
			list = *lst;
		}
		if (list == NULL)
			return (NULL); //clear lst
		list->split_args = ft_split(av[arg], ' '); //dup dans liste chainee
		if (list->split_args == NULL)
			return (NULL); //exit
		if (list->split_args[0][0] == '/')
		{
			if (access(*split_args, X_OK) == 0)
			{
				list->path = *(list->split_args); //strdup, check quand meme access quand exec commande au cas ou ne marche pas
				printf("Le bon chemin est : %s\n", list->path);
			}
		}
		else
		{
			*(list->split_args) = ft_strjoin("/", *(list->split_args));
			if (*(list->split_args) == NULL)
				return (NULL);
			i = 0;
			while (split_path[i] && i != -1)
			{
				list->path = ft_strjoin(split_path[i], *(list->split_args));
				if (list->path == NULL)
					return (NULL);
				if (access(list->path, X_OK) == 0)
					i = -2;
				else
				{
					free(list->path);
					list->path = NULL;
				}
				i++;
			}
		}
		arg++;
	}
	return (*lst);
}

int	main(int ac, char **av, char **env)
{
	int		pipe_fd[2];
	int		file_fd[2];
	char	**argv_tab;
	char	**argv_tab2;
	int		pid;
	int		nb;
	t_list	*lst;

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
	lst = NULL;
	create_pipe(pipe_fd);
	file_check(av[1], av[ac - 1], file_fd);
	lst = access_path(ac, av, env, &lst);
	write(1, lst->path, 5);
	// dprintf(2, "Le bon chemin est : %s\n", lst->path);
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
		if (execve(lst->path, lst->split_args, env) == -1)
			perror ("execve"); //free
		close(pipe_fd[OUT]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		dprintf(2, "%p\n", lst->next);
		lst = lst->next;
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
			if (execve(lst->path, lst->split_args, env) == -1)
				perror ("execve"); //free;
			close(pipe_fd[IN]);
			exit(0);
		}
	}
	return (0);
}