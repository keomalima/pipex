/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:15:08 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/22 16:26:19 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_run(t_filed *file)
{
	int	fd[2];
	int	pid1;
	int	pid2;

	pipe(fd);
	pid1 = fork();
	if (pid1 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		dup2(file->fd_out, STDOUT_FILENO);
		close(fd[0]);
		execve(file->second_cmds[0], file->second_cmds, NULL);
	}
	else
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			close(fd[0]);
			dup2(file->fd_in, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execve(file->first_cmds[0], file->first_cmds, NULL);
		}
		close(fd[0]);
		close(fd[1]);
		waitpid(pid1, NULL, 0);
		waitpid(pid2, NULL, 0);
	}
	return (0);
}

int	pipex(char **av, char **env)
{
	t_filed	file;

	access_check(&file, av);
	if (args_parse(&file, av, env) == 1)
		return (1);
	if (pipex_run(&file) == 1)
		return (1);
	free_split(file.first_cmds);
	free_split(file.second_cmds);
	free_split(file.bin_paths);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ac == 5)
	{
		if (pipex(av, env) == 1)
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
