/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:17:07 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/28 13:23:54 by keomalima        ###   ########.fr       */
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
# include "libft/libft.h"
# include "libft/ft_printf.h"
# include "libft/get_next_line.h"

# define RESET "\x1b[0m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"

typedef struct s_cmds
{
	char	**cmd_args;
}				t_cmds;

typedef struct s_filed
{
	int		fd_in;
	int		fd_out;
	int		ac;
	char	**bin_paths;
	t_cmds	**cmds;
}				t_filed;

void	access_check(t_filed *file, char **av, int ac);
void	free_split(char **arr);
void	exit_handler(const char *err_msg);
void	close_fd(t_filed *file, int fd[2]);
int		parse_prog_args(t_filed *file, int ac, char **av, char **env);
int		pipex_run(t_filed *file);
void	free_cmds_memory(t_filed *file);

#endif
