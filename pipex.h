/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:17:07 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/22 15:28:59 by keomalima        ###   ########.fr       */
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

typedef struct s_filed
{
	int		fd_in;
	int		fd_out;
	char	**first_cmds;
	char	**second_cmds;
	char	**bin_paths;
}					t_filed;

void	access_check(t_filed *file, char **av);
void	free_split(char **arr);
void	exit_handler(const char *err_msg);
int		args_parse(t_filed *file, char **av, char **env);

#endif
