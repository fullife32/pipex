int	create_list(int ac, char **av, t_list **lst, t_pipex *pipex)
{
	int		arg;
	t_list	*list;

	if (split_env(pipex) == -1)
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