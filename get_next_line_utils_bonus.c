/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 15:53:23 by sedemir           #+#    #+#             */
/*   Updated: 2024/12/06 16:22:24 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(const char *s)
{
	int	len;

	len = 0;
	while (s[len] != '\0')
		++len;
	return (len);
}

char	*ft_strdup(const char *s1)
{
	int		idx;
	char	*res;

	res = (char *)malloc(ft_strlen(s1) + 1);
	if (!res)
		return (NULL);
	idx = -1;
	while (s1[++idx] != '\0')
		res[idx] = s1[idx];
	res[idx] = '\0';
	return (res);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_substr(char *s, unsigned int start, int len)
{
	char	*res;
	int		i;
	int		j;
	int		slen;

	slen = ft_strlen(s);
	if (!s || len <= 0)
		return (NULL);
	if (len > slen)
		len = slen;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = start;
	j = 0;
	while (i < slen && j < len)
	{
		res[j] = s[i];
		j++;
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	*free_stash(char **stash, int cline)
{
	char	*line;

	if (!*stash)
		return (NULL);
	if (cline == 0)
	{
		if (*stash)
		{
			free(*stash);
			*stash = NULL;
		}
		return (NULL);
	}
	else if (cline == 1)
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
		return (line);
	}
	return (NULL);
}
