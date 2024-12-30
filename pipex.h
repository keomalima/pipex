/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:17:07 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/30 13:16:58 by keomalima        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"

# define RESET "\x1b[0m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"

typedef struct s_cmd
{
	char	**cmd_args;
}				t_cmd;

typedef struct s_filed
{
	int		fd_in;
	int		fd_out;
	int		ac;
	int		*pid;
	int		**pipe_fd;
	char	**bin_paths;
	t_cmd	**cmds;
}				t_filed;

int		parse_prog_args(t_filed *file, int ac, char **av, char **env);
void	access_check(t_filed *file, char **av, int ac);
void	free_split(char **arr);
void	exit_handler(const char *err_msg);
void	pipex_run_pipes(t_filed *file, char **env);
void	free_cmds_memory(t_filed *file);
void	malloc_n_open_pipes_fd(t_filed *file);
void	clean_memory_and_exit(t_filed *file, char *err_msg);
void	close_all_fds(t_filed *file);
void	close_unused_pipes_fd(t_filed *file, int i);
void	wait_for_children(t_filed *file, int num_children);
void	clean_memory(t_filed *file);

#endif
