/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:03:03 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/25 00:55:52 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_run(t_filed *file)
{
	int	pids[file->ac];
	int	pipes[file->ac + 1][2];
	int	i;
	int	j;
	int x;
	int	y;

	i = 0;
	while (file->ac + 1 > i)
		pipe(pipes[i++]);

	i = 0;
	while (file->ac > i)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			j = 0;
			while (file->ac + 1 > j)
			{
				if (i != j)
					close(pipes[j][0]);
				if (i + 1 != j)
					close(pipes[j][1]);
				j++;
			}
			read(pipes[i][0], &x, sizeof(int));
			printf("(%d) Got %d\n", i, x);
			x++;
			write(pipes[i + 1][1], &x, sizeof(int));
			printf("(%d) Sent %d\n", i, x);
			close(pipes[i][0]);
			close(pipes[i + 1][1]);
			return 0;
		}
		i++;
	}

	//Main process
	j = 0;
	while (file->ac + 1 > j)
	{
		if (j != file->ac)
			close(pipes[j][0]);
		if (j != 0)
			close(pipes[j][1]);
		j++;
	}

	y = 5;
	printf("Main process sent %d\n", y);
	write(pipes[0][1], &y, sizeof(int));
	read(pipes[file->ac][0], &y, sizeof(int));
	printf("The final result is %d\n", y);
	close(pipes[0][1]);
	close(pipes[file->ac][0]);
	i = 0;

	while (file->ac > i)
	{
		wait(NULL);
		i++;
	}
	return 0;
}
