/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:15:08 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/20 13:23:44 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	access_check(char **av, t_filed *file)
{
	int	access_write;

	access_write = access(av[4], W_OK);
	file->fd = open(av[1], O_RDONLY);
	if (!file->fd || access_write == -1)
	{
		if (!file->fd)
			ft_printf("%s: %s\n"RESET, strerror(errno), av[1]);
		else
			ft_printf("%s: %s\n"RESET, strerror(errno), av[4]);
		if (file->fd != -1)
			close(file->fd);
		return (1);
	}
	file->infile = av[1];
	file->first_cmd = av[2];
	file->second_cmd = av[3];
	file->outfile = av[4];
	return (0);
}

int	pipex(char **av)
{
	t_filed	file_info;

	if (access_check(av, &file_info) == 1)
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
