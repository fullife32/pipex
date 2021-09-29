/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 17:00:48 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/29 17:46:49 by eassouli         ###   ########.fr       */
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

int	split_env(char **env, t_pipex *pipex)
{
	while (*env && ft_strncmp(*env, "PATH=", 5) != 0)
		env++;
	if (*env == NULL)
	{
		write(1, "pipex : No path for command found\n", 34); // A changer
		return (-1);
	}
	pipex->env_path = ft_split(*env, ':');
	if (pipex->env_path == NULL)
		return (-1); // exit
	*pipex->env_path += 5;
	return (0);
}

int	access_path(t_list *list, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->env_path[i] && list->path == NULL)
	{
		list->path = ft_strjoin(pipex->env_path[i], pipex->path_tmp);
		if (list->path == NULL)
			return (-1);
		if (access(list->path, X_OK) == -1)
		{
			free(list->path);
			list->path = NULL;
		}
		i++;
	}
	return (0);
}

int	split_args(int arg, char **av, t_list *list, t_pipex *pipex)
{
	list->args = ft_split(av[arg], ' '); //si pas d'arg fix pipe marche quand meme
	if (list->args == NULL)
		return (-1); //tout free
	if (*(list->args) && **(list->args) != '/')
	{
		pipex->path_tmp = ft_strjoin("/", *(list->args));
		if (pipex->path_tmp == NULL)
			return (-1);
		if (access_path(list, pipex) == -1)
			return (-1);
	}
	if (*(list->args) != NULL && list->path == NULL)
		list->path = ft_strdup(*(list->args)); //strdup, check quand meme access quand exec commande au cas ou ne marche pas
	if (list->path == NULL)
		return (-1);
	return (0);
}

int	cmd_path(int ac, char **av, char **env, t_list **lst, t_pipex *pipex)
{
	int		arg;
	t_list	*list;

	if (split_env(env, pipex) == -1)
		return (-1); //free a la fin
	if (pipex->env_path == NULL)
		return (-1);
	arg = 2;
	list = NULL;
	while (arg < ac - 1)
	{
		if (list == NULL)
		{
			*lst = ft_lstnew(NULL);
			list = *lst;
		}
		else
		{
			list->next = ft_lstnew(list);
			list = list->next;
		}
		if (list == NULL)
			return (-1); //clear lst
		if (create_pipe(list->pipe_fd) == -1)
			return (-1);
		if (arg == 2 && pipex->file_fd[IN] == -1)
			list->fail = 1;
		if (split_args(arg, av, list, pipex) == -1)
			return (-1);
		arg++;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
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
	pipex.path_tmp = NULL; //a free
	pipex.env_path = NULL;
	first = &lst;
	file_check(av[1], av[ac - 1], pipex.file_fd);
	if (cmd_path(ac, av, env, &lst, &pipex) == -1)
		return (-1); //free correctement
	if (lst->fail == 1)
		lst = lst->next;
	while (lst)
	{
		pipex.pid = fork(); //check unlink
		if (pipex.pid == -1)
			perror("fork");
		if (pipex.pid == 0)
		{
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
			if (access(lst->path, X_OK) == 0)
			{
				if (execve(lst->path, lst->args, env) == -1) //erreur si fichier1 non ouvert
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
			close(lst->pipe_fd[OUT]);
			if (lst)
				lst = lst->next;
		}
	}
	return (0);
}
