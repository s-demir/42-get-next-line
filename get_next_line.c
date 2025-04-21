/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:52:56 by sedemir           #+#    #+#             */
/*   Updated: 2024/12/06 16:24:18 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

char	ft_line_check(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	i = -1;
	while (s[++i] != '\0')
		if (s[i] == '\n')
			return (1);
	return (0);
}

char	*ft_copy(char *save, char *text)
{
	char	*res;

	res = 0;
	if (!save && text)
	{
		res = ft_strdup(text);
		if (!res)
			return (NULL);
		return (res);
	}
	res = ft_strjoin(save, text);
	free_stash(&save, 0);
	return (res);
}

char	*ft_before_newline(char *save)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	if (!save)
		return (0);
	while (save[i] != '\n')
		i++;
	new = malloc(i + 2);
	if (!new)
		return (0);
	j = 0;
	while (j < i + 1)
	{
		new[j] = save[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

char	*ft_after_newline(char *save)
{
	int		i;
	char	*res;

	i = 0;
	if (!save)
		return (NULL);
	while (save[i] != '\n')
		i++;
	if (save[i + 1] == '\0')
		return (free_stash(&save, 0));
	res = ft_substr(save, i + 1, ft_strlen(save));
	if (!res)
	{
		free_stash(&save, 0);
		return (NULL);
	}
	free_stash(&save, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	long		r_count;
	char		text[BUFFER_SIZE + 1];
	static char	*save = NULL;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_stash(&save, 0));
	r_count = 1;
	while (r_count > 0)
	{
		r_count = read(fd, text, BUFFER_SIZE);
		if ((r_count <= 0 && !save) || r_count == -1)
			return (free_stash(&save, 0));
		text[r_count] = '\0';
		save = ft_copy(save, text);
		if (ft_line_check(save))
		{
			line = ft_before_newline(save);
			if (!line)
				return (free_stash(&save, 0));
			return (save = ft_after_newline(save), line);
		}
	}
	return (free_stash(&save, 1));
}
