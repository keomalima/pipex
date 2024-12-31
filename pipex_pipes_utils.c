/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:32:45 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/31 12:11:03 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_handler(const char *err_msg)
{
	if (errno != 0)
		ft_printf("%s: %s\n", strerror(errno), err_msg);
	else
		ft_printf("%s\n", err_msg);
	exit(EXIT_FAILURE);
}

void	wait_for_children(t_filed *file, int num_children)
{
	while (num_children-- > 0)
	{
		if (wait(NULL) == -1)
			clean_memory_and_exit(file, "error waiting for children");
	}
}

void	clean_memory_and_exit(t_filed *file, char *err_msg)
{
	int	i;

	i = 0;
	if (file->pipe_fd)
	{
		while (file->ac - 1 > i)
			free(file->pipe_fd[i++]);
		free(file->pipe_fd);
	}
	if (file->pid)
		free(file->pid);
	free_cmds_memory(file);
	free_split(file->bin_paths);
	exit_handler(err_msg);
}

void	close_all_fds(t_filed *file)
{
	int	i;

	i = 0;
	while (file->ac - 1 > i)
	{
		close(file->pipe_fd[i][0]);
		close(file->pipe_fd[i][1]);
		i++;
	}
	close(file->fd_in);
	close(file->fd_out);
}

void	malloc_n_open_pipes_fd(t_filed *file)
{
	int	i;

	i = 0;
	file->pipe_fd = NULL;
	file->pipe_fd = malloc(sizeof(int *) * (file->ac - 1));
	if (!file->pipe_fd)
		clean_memory_and_exit(file, "failed to allocate memory to fd column");
	while (file->ac - 1 > i)
	{
		file->pipe_fd[i] = malloc (sizeof(int) * 2);
		if (!file->pipe_fd[i])
			clean_memory_and_exit(file, "failed to allocate memory for fd row");
		i++;
	}
	i = 0;
	while (file->ac - 1 > i)
	{
		if (pipe(file->pipe_fd[i]) == -1)
			clean_memory_and_exit(file, "failed to create pipes");
		i++;
	}
}

