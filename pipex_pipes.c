/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:03:03 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/30 13:48:06 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup2(t_filed *file, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		clean_memory_and_exit(file, "failed to dup2");
}

void	swap_pipes_fd(t_filed *file, int i)
{
	if (i == 0)
	{
		ft_dup2(file, file->fd_in, STDIN_FILENO);
		ft_dup2(file, file->pipe_fd[i][1], STDOUT_FILENO);
	}
	else if (i == file->ac - 1)
	{
		ft_dup2(file, file->pipe_fd[i - 1][0], STDIN_FILENO);
		ft_dup2(file, file->fd_out, STDOUT_FILENO);
	}
	else
	{
		ft_dup2(file, file->pipe_fd[i - 1][0], STDIN_FILENO);
		ft_dup2(file, file->pipe_fd[i][1], STDOUT_FILENO);
	}
}

void	pipex_run_pipes(t_filed *file, char **env)
{
	int	i;

	file->pid = malloc(sizeof(int) * file->ac);
	if (!file->pid)
		clean_memory_and_exit(file, "failed to allocate memory to pid");
	malloc_n_open_pipes_fd(file);
	i = 0;
	while (file->ac > i)
	{
		file->pid[i] = fork();
		if (file->pid[i] == -1)
			clean_memory_and_exit(file, "failed to fork");
		if (file->pid[i] == 0)
		{
			swap_pipes_fd(file, i);
			close_all_fds(file);
			if (execve(file->cmds[i]->cmd_args[0],
					file->cmds[i]->cmd_args, env) == -1)
				clean_memory_and_exit(file, "failed to execve");
		}
		i++;
	}
	close_all_fds(file);
	wait_for_children(file, i);
}
