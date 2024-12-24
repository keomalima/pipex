/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:03:03 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/24 14:17:18 by keomalima        ###   ########.fr       */
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

//Read from previous pipe and pass to outputfile
int	pipe_end(t_filed *file, char **cmd, int fd[2])
{
	if (ft_dup(file, fd, fd[0], STDIN_FILENO) == -1)
		return (1);
	// if (ft_dup(file, fd, file->fd_out, STDOUT_FILENO) == -1)
	// 	return (1);
	close_fd(file, fd);
	ft_execve(cmd);
	return (0);
}

// //Read from file and pass to pipes ends
int	pipe_start(t_filed *file, char **cmd, int fd[2])
{
	if (ft_dup(file, fd, file->fd_in, STDIN_FILENO) == 1)
		return (1);
	if (ft_dup(file, fd, fd[1], STDOUT_FILENO) == -1)
		return (1);
	close_fd(file, fd);
	ft_execve(cmd);
	return (0);
}

int	pipex_run(t_filed *file)
{
	int	pid[file->ac];
	int	fd[2];
	int	i;

	i = 0;
	pipe(fd);
	while (file->ac > i)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (i == 0)
			{
				printf("Iteration %i\n", i);
				pipe_start(file, file->cmds[i]->cmd_args, fd);
			}
			else if (i == file->ac - 1)
			{
				printf("Iteration end %i\n", i);
				pipe_end(file, file->cmds[i]->cmd_args, fd);
			}
			break;
		}
		else
		{
			waitpid(pid[i], NULL, 0);
			close_fd(file, fd);
		}
		i++;
	}
	return (0);
}
