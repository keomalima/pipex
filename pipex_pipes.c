/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:03:03 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/23 20:01:43 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_dup(t_filed *file, int fd[2], int old_fd, int new_fd)
{
	if (dup2(old_fd, new_fd) == -1)
	{
		close_fd(file, fd);
		ft_printf(RED"%s: %s\n"RESET, "Error", strerror(errno));
		return (1);
	}
	return (0);
}

int	ft_execve(char **file)
{
	if (execve(file[0], file, NULL) == -1)
	{
		ft_printf(RED"%s: %s\n"RESET, "Error", strerror(errno));
		return (1);
	}
	return (0);
}

int	pipe_read(t_filed *file, int fd[2])
{
	if (ft_dup(file, fd, file->fd_in, STDIN_FILENO) == 1)
		return (1);
	if (ft_dup(file, fd, fd[1], STDOUT_FILENO) == -1)
		return (1);
	close_fd(file, fd);
	return (0);
}

int	pipe_write(t_filed *file, int fd[2])
{
	if (ft_dup(file, fd, fd[0], STDIN_FILENO) == -1)
		return (1);
	if (ft_dup(file, fd, file->fd_out, STDOUT_FILENO) == -1)
		return (1);
	close_fd(file, fd);
	return (0);
}

int	pipex_run(t_filed *file)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == -1)
	{
		ft_printf(RED"%s: %s\n"RESET, "Error", strerror(errno));
		return (1);
	}
	if (pid1 == 0)
		if (pipe_read(file, fd) == 1)
			return (1);
	pid2 = fork();
	if (pid2 == -1)
	{
		ft_printf(RED"%s: %s\n"RESET, "Error", strerror(errno));
		return (1);
	}
	if (pid2 == 0)
		if (pipe_write(file, fd) == 1)
			return (1);
	close_fd(file, fd);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
