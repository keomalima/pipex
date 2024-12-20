/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:15:08 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/20 14:43:14 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	redirect_fd(t_filed *file)
{
	if (dup2(file->fd_in, 0) < 0 || dup2(file->fd_out, 1) < 0)
	{
		close(file->fd_in);
		close(file->fd_out);
		return (1);
	}
	close(file->fd_in);
	close(file->fd_out);
	return (0);
}

int	access_check(char **av, t_filed *file)
{
	file->fd_in = open(av[1], O_RDONLY);
	if (file->fd_in < 0)
		ft_printf(RED"%s: %s\n"RESET, strerror(errno), av[1]);
	file->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file->fd_out < 0)
	{
		ft_printf(RED"%s: %s\n"RESET, strerror(errno), av[4]);
		if (file->fd_in != -1)
			close(file->fd_in);
	}
	if (file->fd_in < 0 || file->fd_out < 0)
		return (1);
	return (0);
}

int	pipex(char **av)
{
	t_filed	file;

	if (access_check(av, &file) == 1 || redirect_fd(&file) == 1)
		return (1);
	return (0);
}


int	main(int ac, char **av)
{
	if (ac == 5)
	{
		if (pipex(av) == 1)
			return (1);
	}
	else
	{
		if (ac < 5)
			ft_printf(RED"Error: Too few arguments\n"RESET);
		else
			ft_printf(RED"Error: Too many arguments\n"RESET);
		return (1);
	}
	return (0);
}
