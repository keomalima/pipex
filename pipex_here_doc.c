/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:30:50 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/31 16:29:13 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	loop_arg_identifier(t_filed *file)
{
	int	i;

	i = 0;
	while (file->ac > i)
	{
		ft_printf("pipe ");
		i++;
	}
	ft_printf("heredoc> ");
}

void	failed_putstr(t_filed *file, char *str, int fd[2])
{
	free(str);
	close(fd[0]);
	close(fd[1]);
	clean_memory_and_exit(file, "failed to write to pipe");
}

void	pipex_here_doc(t_filed *file)
{
	int		fd[2];
	char	*str;

	if (!file->is_here_doc)
		return ;
	if (pipe(fd) < 0)
		clean_memory_and_exit(file, "pipe failed");
	while (1)
	{
		loop_arg_identifier(file);
		str = get_next_line(STDIN_FILENO);
		if (!str)
			clean_memory_and_exit(file, "failed to read from input");
		if (ft_strncmp(str, file->limiter, ft_strlen(file->limiter)) == 0)
		{
			free(str);
			break ;
		}
		if (ft_putstr_fd(str, fd[1]) < 0)
			failed_putstr(file, str, fd);
		free(str);
	}
	close(fd[1]);
	file->fd_in = fd[0];
}
