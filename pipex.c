/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:15:08 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/30 11:11:47 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex(char **av, int ac, char **env)
{
	t_filed	file;

	access_check(&file, av, ac);
	if (parse_prog_args(&file, ac, av, env) == 1)
	{
		close(file.fd_in);
		close(file.fd_out);
		return (1);
	}
	pipex_run_pipes(&file, env);
	free_cmds_memory(&file);
	free_split(file.bin_paths);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	if (ac > 4)
	{
		if (pipex(av, ac, env) == 1)
			return (1);
	}
	else
	{
		ft_printf(RED"Error: Too few arguments\n"RESET);
		return (1);
	}
	return (0);
}
