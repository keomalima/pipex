/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:03:03 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/30 11:51:04 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_dup2(t_filed *file, int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
		clean_memory_and_exit(file, "failed to dup2");
}

void	swap_pipes_fd(t_filed *file, int (*fd)[2], int i)
{
	if (i == 0)
	{
		ft_dup2(file, file->fd_in, STDIN_FILENO);
		ft_dup2(file, fd[i][1], STDOUT_FILENO);
	}
	else if (i == file->ac - 1)
	{
		ft_dup2(file, fd[i - 1][0], STDIN_FILENO);
		ft_dup2(file, file->fd_out, STDOUT_FILENO);
	}
	else
	{
		ft_dup2(file, fd[i - 1][0], STDIN_FILENO);
		ft_dup2(file, fd[i][1], STDOUT_FILENO);
	}
	close(fd[i][1]);
	close(fd[i - 1][0]);
	close(file->fd_in);
	close(file->fd_out);
}

void	pipex_run_pipes(t_filed *file, char **env)
{
	int	pid[file->ac];
	int	fd[file->ac - 1][2];
	int	i;

	open_pipes_fd(file, fd);
	i = 0;
	while (file->ac > i)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			clean_memory_and_exit(file, "failed to fork");
		if (pid[i] == 0)
		{
			close_pipes_fd(file, fd, i);
			swap_pipes_fd(file, fd, i);
			if (execve(file->cmds[i]->cmd_args[0],
					file->cmds[i]->cmd_args, env) == -1)
				clean_memory_and_exit(file, "failed to execve");
		}
		i++;
	}
	close_all_fds(file, fd);
	wait_for_children(file, i);
}
