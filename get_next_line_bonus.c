/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:13:21 by sedemir           #+#    #+#             */
/*   Updated: 2024/12/06 16:26:26 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

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

char	ft_line_check(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = -1;
	while (s[++i] != '\0')
		if (s[i] == '\n')
			return (1);
	return (0);
}

char	*ft_before_newline(char *save)
{
	char	*nl;
	size_t	i;
	size_t	j;

	i = 0;
	if (!save)
		return (0);
	while (save[i] != '\n')
		i++;
	nl = malloc(i + 2);
	if (!nl)
		return (0);
	j = 0;
	while (j < i + 1)
	{
		nl[j] = save[j];
		j++;
	}
	nl[j] = '\0';
	return (nl);
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
	char		*line;
	static char	*save[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_stash(&save[fd], 0));
	r_count = 1;
	while (r_count > 0)
	{
		r_count = read(fd, text, BUFFER_SIZE);
		if ((r_count <= 0 && !save[fd]) || r_count == -1)
			return (free_stash(&save[fd], 0));
		text[r_count] = '\0';
		save[fd] = ft_copy(save[fd], text);
		if (ft_line_check(save[fd]))
		{
			line = ft_before_newline(save[fd]);
			if (!line)
				return (free_stash(&save[fd], 0));
			return (save[fd] = ft_after_newline(save[fd]), line);
		}
	}
	return (free_stash(&save[fd], 1));
}
