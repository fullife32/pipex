/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:17:08 by eassouli          #+#    #+#             */
/*   Updated: 2021/09/30 17:38:37 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PIPEX_H
#define	PIPEX_H

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define IN 0
#define OUT 1

#define FREE_ALL -2
#define FREE_FORK -3

typedef struct s_pipex
{
	int				pid;
	int				file_fd[2];
	char			*path_tmp;
	char			**env_path;
}					t_pipex;

typedef struct s_list
{
	int				fail;
	int				pipe_fd[2];
	char			*path;
	char			**args;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

int		dup_stdin(t_list *lst, t_pipex *pipex);
int		dup_stdout(t_list *lst, t_pipex *pipex);
void	exec_cmd(char **env, t_list *lst, t_pipex *pipex);

int		create_pipe(int pipefd[]);

int		split_env(char **env, t_pipex *pipex);
int		access_path(t_list *list, t_pipex *pipex);
int		split_args(int arg, char **av, t_list *list, t_pipex *pipex);
int		create_list(int ac, char **av, char **env, t_list **lst, t_pipex *pipex);

void	init_check(int ac, char **env);
void	file_check(char *path1, char *path2, int file_fd[2]);

void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
t_list	*ft_lstnew(t_list *lst);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif