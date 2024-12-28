/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:38:58 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/28 13:24:00 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(t_filed *file, int fd[2])
{
	if (file->fd_in)
		close(file->fd_in);
	if (file->fd_out)
		close(file->fd_in);
	if (fd[0])
		close(fd[0]);
	if (fd[1])
		close(fd[1]);
}

void	exit_handler(const char *err_msg)
{
	if (errno != 0)
		ft_printf(RED"%s: %s\n"RESET, strerror(errno), err_msg);
	else
		ft_printf(RED"%s\n"RESET, err_msg);
	exit(EXIT_FAILURE);
}

void	free_cmds_memory(t_filed *file)
{
	int	i;
	int	j;

	i = 0;
	while (file->cmds[i])
	{
		j = 0;
		if (file->cmds[i]->cmd_args)
		{
			while (file->cmds[i]->cmd_args[j])
				free(file->cmds[i]->cmd_args[j++]);
			free(file->cmds[i]->cmd_args);
		}
		free(file->cmds[i]);
		i++;
	}
	free(file->cmds);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	access_check(t_filed *file, char **av, int ac)
{
	file->fd_in = open(av[1], O_RDONLY);
	if (file->fd_in < 0)
		exit_handler(av[1]);
	file->fd_out = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file->fd_out < 0)
	{
		if (file->fd_in != -1)
			close(file->fd_in);
		exit_handler(av[4]);
	}
}
