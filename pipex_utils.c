/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 09:38:58 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/22 13:41:13 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_handler(const char *err_msg)
{
	if (errno != 0)
		ft_printf(RED"%s: %s\n"RESET, strerror(errno), err_msg);
	else
		ft_printf(RED"%s\n"RESET, err_msg);
	exit(EXIT_FAILURE);
}

void	free_split(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

int	access_check(t_filed *file, char **av)
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