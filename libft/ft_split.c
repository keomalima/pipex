/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kricci-d <kricci-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:02:15 by kricci-d          #+#    #+#             */
/*   Updated: 2024/12/17 13:19:25 by kricci-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	tab_len(char const *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			while (*s && *s != c)
				s++;
		}
		while (*s && *s == c)
			s++;
	}
	return (i);
}

static	void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i++]);
			tab = NULL;
		}
		free(tab);
	}
}

char	*fill_str(const char *s, char c)
{
	int		i;
	int		str_len;
	char	*str;

	i = 0;
	str_len = 0;
	while (s[i] && s[i] != c)
	{
		str_len++;
		i++;
	}
	str = malloc(sizeof(char) * str_len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (*s && *s != c)
		str[i++] = *s++;
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;

	tab = malloc(sizeof(char *) * (tab_len(s, c) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			tab[i++] = fill_str(s, c);
			if (!tab[i - 1])
			{
				free_tab(tab);
				return (NULL);
			}
			while (*s && *s != c)
				s++;
		}
		while (*s && *s == c)
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
