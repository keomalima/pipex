/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:03:03 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/23 15:51:09 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipe_read(t_filed *file, int fd[2])
{
	if (!file || !file->first_cmds || !file->first_cmds[0])
	{
		ft_printf("Invalid file or command structure");
		return (1);
	}
	if (dup2(file->fd_in, STDIN_FILENO) == -1)
	{
		close_fd(file, fd);
		ft_printf("Failed to execute dup2\n");
		return (1);
	}
	if (dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close_fd(file, fd);
		ft_printf("Failed to execute dup2\n");
		return (1);
	}
	close_fd(file, fd);
	if (execve(file->first_cmds[0], file->first_cmds, NULL) == -1)
	{
		ft_printf("Failed to execute execve\n");
		return (1);
	}
	return (0);
}

int	pipe_write(t_filed *file, int fd[2])
{
	if (!file || !file->second_cmds || !file->second_cmds[0])
	{
		ft_printf("Invalid file or command structure");
		return (1);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1)
	{
		close_fd(file, fd);
		ft_printf("Failed to execute dup2\n");
		return (1);
	}
	if (dup2(file->fd_out, STDOUT_FILENO) == -1)
	{
		close_fd(file, fd);
		ft_printf("Failed to execute dup2\n");
		return (1);
	}
	close_fd(file, fd);
	if (execve(file->second_cmds[0], file->second_cmds, NULL) == -1)
	{
		ft_printf("Failed to execute execve\n");
		return (1);
	}
	return (0);
}

int	pipex_run(t_filed *file)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		if (pipe_read(file, fd) == 1)
			return (1);
	}
	pid2 = fork();
	if (pid2 == 0)
	{
		if (pipe_write(file, fd) == 1)
			return (1);
	}
	close_fd(file, fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
