/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:15:08 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/22 15:20:42 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	pipex_run(t_filed *file)
{
	(void)file;

	return (0);
}

int	pipex(char **av, char **env)
{
	t_filed	file;

	if (access_check(&file, av) == 1)
		return (1);
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
