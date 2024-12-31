/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_arg_parse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 11:27:52 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/31 16:29:45 by keomalima        ###   ########.fr       */
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

char	*prefix_cmd_path(t_filed *file, t_cmd *cmd)
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

t_cmd	*parse_cmd_args(t_filed *file, char *args)
{
	t_cmd	*cmd;

	cmd = malloc (sizeof(t_cmd) * 1);
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
	int	bonus_var;

	parse_path_env(file, env);
	if (file->is_here_doc)
		bonus_var = 1;
	else
		bonus_var = 0;
	file->cmds = malloc (sizeof(t_cmd *) * (ac - 2 - bonus_var));
	if (!file->cmds)
		exit_handler("Failed to parse cmds");
	i = 0;
	while (ac - 3 - bonus_var > i)
	{
		file->cmds[i] = parse_cmd_args(file, av[i + 2 + bonus_var]);
		if (!file->cmds[i])
		{
			free_cmds_memory(file);
			return (1);
		}
		i++;
	}
	file->cmds[i] = NULL;
	file->ac = ac - 3 - bonus_var;
	return (0);
}
