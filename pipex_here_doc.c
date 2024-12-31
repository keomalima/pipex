/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 11:30:50 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/31 14:03:50 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex_here_doc(t_filed *file)
{
	char	*str;

	if (!file->is_here_doc)
		return ;
	while (1)
	{
		str = get_next_line(file->fd_in);
		if (!str)
			exit_handler("failed to get str from input");
		if (ft_strncmp(str, file->limiter, ft_strlen(file->limiter)) == 0)
		{
			free(str);
			break ;
		}
		if (ft_putstr_fd(str, file->pipe_fd[0][1] < 0))
		{
			free(str);
			exit_handler("Failed to write to pipe");
		}
		free(str);
	}
}