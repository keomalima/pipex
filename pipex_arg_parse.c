/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_arg_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:27:52 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/22 14:42:18 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_bin_path(t_filed *file, char *cmd, char *first_arg)
{
	char	*file_path;
	int		i;

	i = 0;
	while (file->bin_paths[i])
	{
		file_path = ft_strjoin(file->bin_paths[i], cmd);
		if (!file_path)
		{
			free(cmd);
			ft_printf("Failed to strjoin cmd to PATH env");
			return (NULL);
		}
		if (access(file_path, X_OK) == 0)
		{
			free(cmd);
			free(first_arg);
			first_arg = NULL;
			return (file_path);
		}
		free(file_path);
		i++;
	}
	ft_printf("Command not found: %s\n", first_arg);
	return (NULL);
}

char	**cmd_args_split(t_filed *file, char *args)
{
	char	**cmd_args;
	char	*cmd_path;
	(void)file;

	cmd_args = ft_split(args, 32);
	if (!cmd_args)
	{
		ft_printf("Failed to split cmd args string\n");
		return (NULL);
	}
	cmd_path = ft_strjoin("/", cmd_args[0]);
	if (!cmd_path)
	{
		ft_printf("Failed to strjoin cmd path separator\n");
		free_split(cmd_args);
		return (NULL);
	}
	cmd_args[0] = find_bin_path(file, cmd_path, cmd_args[0]);
	if (!cmd_args[0])
	{
		free_split(cmd_args);
		ft_printf("Failed to find cmd bin path\n");
		return (NULL);
	}
	return (cmd_args);
}

void	find_bin_dir_paths(t_filed *file, char **env)
{
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5))
		{
			file->bin_paths = ft_split(*env + 5, ':');
			if (!file->bin_paths)
				exit_handler("Failed to split dir paths");
			return ;
		}
		env++;
	}
	exit_handler("PATH env variable not found");
}

int	args_parse(t_filed *file, char **av, char **env)
{
	(void)av;
	if (!av[2][0] || !av[3][0])
	{
		ft_printf("Command not found\n");
		return (1);
	}
	find_bin_dir_paths(file, env);
	file->first_cmds = cmd_args_split(file, av[2]);
	if (!file->first_cmds)
		return (1);
	// file->second_cmds = args_split(file, av[3]);
	// if (!file->second_cmds)
	// {
	// 	if (file->first_cmds)
	// 		free_split(file->first_cmds);
	// 	return (1);
	// }
	return (0);
}