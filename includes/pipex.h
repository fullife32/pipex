/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eassouli <eassouli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 12:17:08 by eassouli          #+#    #+#             */
/*   Updated: 2021/10/04 18:49:00 by eassouli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>

# define IN 0
# define OUT 1

# define FREE_ALL -2
# define FREE_FORK -3

typedef struct s_pipex
{
	int				ret;
	int				pid;
	int				file_fd[2];
	char			*path_tmp;
	char			**env;
	char			**env_path;
}					t_pipex;

typedef struct s_list
{
	int				pid;
	int				fail;
	int				pipe_fd[2];
	char			*path;
	char			**args;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

void	free_pipex(t_list **first, t_pipex *pipex);

int		dup_stdin(t_list *lst, t_pipex *pipex);
int		dup_stdout(t_list *lst, t_pipex *pipex);
void	exec_cmd(char **env, t_list *lst, t_pipex *pipex);

int		create_pipe(int pipefd[]);

int		split_env(t_pipex *pipex);
int		access_path(t_list *list, t_pipex *pipex);
int		split_args(int arg, char **av, t_list *list, t_pipex *pipex);
int		create_list(int ac, char **av, t_list **lst, t_pipex *pipex);

void	init_check(int ac, char **env);
void	file_check(char *path1, char *path2, int file_fd[2]);

void	del(void **ptr);
void	ft_lstclear(t_list **lst, void (*del)(void **));
void	ft_lstdelone(t_list *lst, void (*del)(void **));
t_list	*ft_lstnew(t_list *lst);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

int		return_value(t_list *lst);

#endif
