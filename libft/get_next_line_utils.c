/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 10:16:44 by keomalima         #+#    #+#             */
/*   Updated: 2024/12/11 10:21:16 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clear_line(char *line)
{
	if (line)
	{
		free(line);
		line = NULL;
	}
	return (NULL);
}

char	*ft_strnjoin(char *line, char *buffer, size_t size)
{
	char	*join;
	size_t	i;
	size_t	j;

	if (!line)
	{
		line = malloc(1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	if (!buffer)
		return (clear_line(line));
	join = malloc(sizeof(char) * (ft_strlen(line) + size) + 1);
	if (!join)
		return (clear_line(line));
	i = -1;
	while (line[++i])
		join[i] = line[i];
	j = 0;
	while (buffer[j] && size > j)
		join[i++] = buffer[j++];
	join[i] = '\0';
	free(line);
	return (join);
}
