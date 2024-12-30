/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:17:07 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/30 11:33:17 by keomalima        ###   ########.fr       */
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
	char	**bin_paths;
	t_cmd	**cmds;
}				t_filed;

void	access_check(t_filed *file, char **av, int ac);
void	free_split(char **arr);
void	exit_handler(const char *err_msg);
int		parse_prog_args(t_filed *file, int ac, char **av, char **env);
void	pipex_run_pipes(t_filed *file, char **env);
void	free_cmds_memory(t_filed *file);
void	open_pipes_fd(t_filed *file, int (*fd)[2]);
void	clean_memory_and_exit(t_filed *file, char *err_msg);
void	close_all_fds(t_filed *file, int (*fd)[2]);
void	close_pipes_fd(t_filed *file, int (*fd)[2], int i);
void	wait_for_children(t_filed *file, int num_children);

#endif
