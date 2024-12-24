/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_arg_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:27:52 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/24 13:18:08 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	parse_path_env(t_filed *file, char **env)
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

char	*get_exec_path(t_filed *file, char *cmd_arg, char *prefixed_cmd)
{
	char	*file_path;
	int		i;

	i = 0;
	while (file->bin_paths[i])
	{
		file_path = ft_strjoin(file->bin_paths[i], prefixed_cmd);
		if (!file_path)
		{
			free(prefixed_cmd);
			ft_printf("Failed to join cmd with PATH dir\n");
			return (NULL);
		}
		if (access(file_path, X_OK) == 0)
		{
			free(prefixed_cmd);
			free(cmd_arg);
			return (file_path);
		}
		free(file_path);
		i++;
	}
	free(prefixed_cmd);
	ft_printf("Command not found: %s\n", cmd_arg);
	return (NULL);
}

char	*prefix_cmd_path(t_filed *file, t_cmds *cmd)
{
	char	*prefixed_cmd;

	prefixed_cmd = ft_strjoin("/", cmd->cmd_args[0]);
	if (!prefixed_cmd)
	{
		ft_printf("Failed to prefix the cmd\n");
		free_split(cmd->cmd_args);
		free(cmd);
		return (NULL);
	}
	cmd->cmd_args[0] = get_exec_path(file, cmd->cmd_args[0], prefixed_cmd);
	if (!cmd->cmd_args[0])
	{
		free_split(cmd->cmd_args);
		free(cmd);
		return (NULL);
	}
	return (prefixed_cmd);
}

t_cmds	*parse_cmd_args(t_filed *file, char *args)
{
	t_cmds	*cmd;

	cmd = malloc (sizeof(t_cmds) * 1);
	if (!cmd)
	{
		ft_printf("Failed to allocate memory for cmd\n");
		return (NULL);
	}
	cmd->cmd_args = ft_split(args, 32);
	if (!cmd->cmd_args)
	{
		ft_printf("Failed to split cmd args string\n");
		free(cmd);
		return (NULL);
	}
	if (!prefix_cmd_path(file, cmd))
		return (NULL);
	return (cmd);
}

int	parse_prog_args(t_filed *file, int ac, char **av, char **env)
{
	int	i;

	parse_path_env(file, env);
	file->cmds = malloc (sizeof(t_cmds *) * (ac - 2));
	if (!file->cmds)
		exit_handler("Failed to parse cmds");
	i = 0;
	while (ac - 3 > i)
	{
		file->cmds[i] = parse_cmd_args(file, av[i + 2]);
		if (!file->cmds[i])
		{
			while (--i > 0)
			{
				free_split(file->cmds[i]->cmd_args);
				free(file->cmds[i]);
			}
			free(file->cmds);
			return (1);
		}
		i++;
	}
	file->cmds[ac - 3] = NULL;
	file->ac = ac - 3;
	return (0);
}
