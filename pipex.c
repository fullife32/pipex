/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/28 19:04:26 by eassouli         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	}
}

char	**split_env(char **split_path, char **env)
{
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
	*split_path += 5;
	return (split_path);
}

int	access_path(int ac, char **av, char **env, t_list **lst, t_pipex *pipex)
{
	int		i;
	int		arg;
	char	**split_path;
	t_list	*list;

	split_path = split_env(split_path, env);
	if (split_path == NULL)
		return (-1);
	arg = 2;
	list = NULL;
	while (arg < ac - 1)
	{
		if (list)
		{
			list->next = ft_lstnew(list);
			list = list->next;
		}
		else
		{
			*lst = ft_lstnew(NULL);
			list = *lst;
		}
		if (list == NULL)
			return (-1); //clear lst
		create_pipe(list->pipe_fd);
		if (arg == 2 && pipex->file_fd[IN] == -1)
			list->fail = 1;
		list->split_args = ft_split(av[arg], ' '); //dup dans liste chainee
		if (list->split_args == NULL)
			return (-1); //exit
		if (**(list->split_args) == '/')
			list->path = *(list->split_args); //strdup, check quand meme access quand exec commande au cas ou ne marche pas
		else
		{
			*(list->split_args) = ft_strjoin("/", *(list->split_args));
			if (*(list->split_args) == NULL)
				return (-1);
			i = 0;
			list->path = NULL;
			while (split_path[i] && list->path == NULL)
			{
				list->path = ft_strjoin(split_path[i], *(list->split_args));
				if (list->path == NULL)
					return (-1);
				if (access(list->path, X_OK) == -1)
				{
					free(list->path);
					list->path = NULL;
				}
				i++;
			}
			if (list->path == NULL)
				list->path = ft_strdup(list->split_args[0] + 1); //segv
		}
		arg++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int		nb;
	t_pipex	pipex;
	t_list	**first;
	t_list	*lst;

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
	lst = NULL;
	first = &lst;
	file_check(av[1], av[ac - 1], pipex.file_fd);
	access_path(ac, av, env, &lst, &pipex);
	// pipex.pid = fork();
	// if (pipex.pid == -1)
	// 	perror("fork");
	// if (pipex.pid == 0)
	// {
		// close(lst->pipe_fd[IN]);
		// if (dup2(pipex.file_fd[IN], IN) == -1)
		// 	perror("dup2"); //exit ?
		// if (dup2(lst->pipe_fd[OUT], OUT) == -1)
		// 	perror("dup2"); //exit ?
		// if (execve(lst->path, lst->split_args, env) == -1)
		// 	perror ("execve"); //free
		// close(lst->pipe_fd[OUT]);
		// exit(EXIT_SUCCESS);
	// }
	// else
	// {
	// if (lst->prev == NULL || lst->fail == 1)
	// 	lst = lst->next;
	while (lst)
	{
		pipex.pid = fork(); //check unlink
		if (pipex.pid == -1)
			perror("fork");
		if (pipex.pid == 0)
		{
			dprintf(2, "%s\n", lst->split_args[0]);
			if (lst->prev == NULL) //si premier IN
			{
				if (dup2(pipex.file_fd[IN], IN) == -1)
					perror("dup2"); //exit ?
				close(lst->pipe_fd[IN]);
			}
			else if (lst->next == NULL) //si dernier IN
			{
				if (dup2(lst->prev->pipe_fd[IN], IN) == -1)
					perror("dup2"); //exit ?
				close(lst->pipe_fd[OUT]);
			}
			else //milieu IN
			{
				if (dup2(lst->prev->pipe_fd[IN], IN) == -1)
					perror("dup2"); //exit ?
			}
			if (lst->next == NULL) //si dernier OUT
			{
				if (dup2(pipex.file_fd[OUT], OUT) == -1)
					perror("dup2"); // exit ?
			}
			else // premier et milieu OUT
			{
				if (dup2(lst->pipe_fd[OUT], OUT) == -1)
					perror("dup2"); // exit ?
			}
			if (lst->path == NULL || access(lst->path, X_OK) == 0)
			{
				if (execve(lst->path, lst->split_args, env) == -1)
					perror ("execve"); //free;
			}
			else
			{
				write(2, lst->path, ft_strlen(lst->path));
				write(2, ": command not found\n", 21);
				close(lst->pipe_fd[IN]);
				close(lst->pipe_fd[OUT]);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			if (lst)
				lst = lst->next;
		}
	}
	return (0);
}
