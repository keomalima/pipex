/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:38:58 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/31 11:24:28 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_memory(t_filed *file)
{
	int	i;

	i = 0;
	while (file->ac - 1 > i)
		free(file->pipe_fd[i++]);
	free(file->pipe_fd);
	free(file->pid);
	free_cmds_memory(file);
	free_split(file->bin_paths);
}

void	free_cmds_memory(t_filed *file)
{
	int	i;

	if (!file || !*file->cmds)
		return ;
	i = 0;
	while (file->cmds[i])
	{
		if (file->cmds[i]->cmd_args)
			free_split(file->cmds[i]->cmd_args);
		free(file->cmds[i]);
		i++;
	}
	free(file->cmds);
}

void	free_split(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	access_check(t_filed *file, char **av, int ac)
{
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		file->fd_in = dup(STDIN_FILENO);
		file->is_here_doc = 1;
		file->limiter = av[2];
	}
	else
	{
		file->fd_in = open(av[1], O_RDONLY);
		file->is_here_doc = 0;
		file->limiter = NULL;
	}
	if (file->fd_in < 0)
			exit_handler(av[1]);
	file->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file->fd_out < 0)
	{
		if (file->fd_in != -1)
			close(file->fd_in);
		exit_handler(av[4]);
	}
}
