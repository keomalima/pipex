/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: keomalima <keomalima@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 11:17:07 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/20 14:31:30 by keomalima        ###   ########.fr       */
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

#define RESET "\x1b[0m"   // Reset color
#define RED "\x1b[31m"  // Red
#define GREEN "\x1b[32m"  // Green
#define YELLOW "\x1b[33m"  // Yellow
#define BLUE "\x1b[34m"  // Blue

typedef struct s_filed
{
	int		fd_in;
	int		fd_out;
	char	*infile;
	char	*outfile;
	char	*first_cmd;
	char	*second_cmd;
}					t_filed;

#endif
