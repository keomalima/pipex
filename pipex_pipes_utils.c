/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_pipes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 11:32:45 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/30 11:15:55 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	free_cmds_memory(file);
	free_split(file->bin_paths);
	exit_handler(err_msg);
}

void	close_all_fds(t_filed *file, int (*fd)[2])
{
	int	i;

	i = 0;
	while (file->ac - 1 > i)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
	close(file->fd_in);
	close(file->fd_out);
}

void	open_pipes_fd(t_filed *file, int (*fd)[2])
{
	int	i;

	i = 0;
	while (file->ac - 1 > i)
	{
		if (pipe(fd[i]) == -1)
			clean_memory_and_exit(file, "failed to create pipes");
		i++;
	}
}

void	close_pipes_fd(t_filed *file, int (*fd)[2], int i)
{
	int	j;

	j = 0;
	while (file->ac - 1 > j)
	{
		if (i != j)
			close(fd[j][1]);
		if (j != i - 1)
			close(fd[j][0]);
		j++;
	}
}
