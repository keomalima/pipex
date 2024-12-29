/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:03:03 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/29 12:05:28 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int pipex_run(t_filed *file)
{
	int pid[file->ac];
	int fd[file->ac - 1][2];
	int i;

	open_pipes(file, fd);
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
			if (execve(file->cmds[i]->cmd_args[0], file->cmds[i]->cmd_args, NULL) == -1)
				clean_memory_and_exit(file, "failed to execve");
		}
		i++;
	}
	close_all_fds(file, fd);
	wait(NULL);
	return (0);
}
