/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:03:03 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/28 17:37:48 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int pipex_run(t_filed *file)
{
	int pid[file->ac];
	int fd[file->ac - 1][2];
	int i;
	int	j;

	i = 0;
	while (file->ac - 1 > i)
		pipe(fd[i++]);
	i = 0;
	while (file->ac > i)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			j = 0;
			if (i == 0)
			{
				while (file->ac - 1 > j)
				{
					if (i != j)
						close(fd[j][1]);
					close(fd[j][0]);
					j++;
				}
				dup2(file->fd_in, STDIN_FILENO);
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
			}
			if (i == file->ac - 1)
			{
				while (file->ac - 1 > j)
				{
					if (j != i - 1)
						close(fd[j][0]);
					close(fd[j][1]);
					j++;
				}
				dup2(fd[i - 1][0], STDIN_FILENO);
				dup2(file->fd_out, STDOUT_FILENO);
				close(fd[i - 1][0]);
			}
			else
			{
				while (file->ac - 1 > j)
				{
					if (j != i - 1)
						close(fd[j][0]);
					if (j != i)
						close(fd[j][1]);
					j++;
				}
				dup2(fd[i - 1][0], STDIN_FILENO);
				dup2(fd[i][1], STDOUT_FILENO);
				close(fd[i][1]);
				close(fd[i - 1][0]);
			}
			execve(file->cmds[i]->cmd_args[0], file->cmds[i]->cmd_args, NULL);
		}
		i++;
	}
	i = 0;
	while (file->ac - 1 > i)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	wait(NULL);
	return (0);
}

// int	pipex_run(t_filed *file)
// {
// 	int	pids[file->ac];
// 	int	pipes[file->ac + 1][2];
// 	int	i;
// 	int	j;
// 	int x;
// 	int	y;

// 	i = 0;
// 	while (file->ac + 1 > i)
// 		pipe(pipes[i++]);

// 	i = 0;
// 	while (file->ac > i)
// 	{
// 		pids[i] = fork();
// 		if (pids[i] == 0)
// 		{
// 			j = 0;
// 			while (file->ac + 1 > j)
// 			{
// 				if (i != j)
// 					close(pipes[j][0]);
// 				if (i + 1 != j)
// 					close(pipes[j][1]);
// 				j++;
// 			}
// 			read(pipes[i][0], &x, sizeof(int));
// 			printf("(%d) Got %d\n", i, x);
// 			x++;
// 			write(pipes[i + 1][1], &x, sizeof(int));
// 			printf("(%d) Sent %d\n", i, x);
// 			close(pipes[i][0]);
// 			close(pipes[i + 1][1]);
// 			return 0;
// 		}
// 		i++;
// 	}

// 	//Main process
// 	j = 0;
// 	while (file->ac + 1 > j)
// 	{
// 		if (j != file->ac)
// 			close(pipes[j][0]);
// 		if (j != 0)
// 			close(pipes[j][1]);
// 		j++;
// 	}

// 	y = 5;
// 	printf("Main process sent %d\n", y);
// 	write(pipes[0][1], &y, sizeof(int));
// 	read(pipes[file->ac][0], &y, sizeof(int));
// 	printf("The final result is %d\n", y);
// 	close(pipes[0][1]);
// 	close(pipes[file->ac][0]);
// 	i = 0;

// 	while (file->ac > i)
// 	{
// 		wait(NULL);
// 		i++;
// 	}
// 	return 0;
// }
