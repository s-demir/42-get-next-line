/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sedemir <sedemir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 15:53:54 by sedemir           #+#    #+#             */
/*   Updated: 2024/12/06 15:33:19 by sedemir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
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

char	*ft_strjoin(char *s1, char *s2)
{
	int		a;
	int		b;
	char	*ptr;

	a = 0;
	b = 0;
	if (!s1 || !s2)
		return (NULL);
	ptr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ptr)
		return (NULL);
	while (s1[a])
	{
		ptr[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		ptr[a] = s2[b];
		a++;
		b++;
	}
	ptr[a] = '\0';
	return (ptr);
}

char	*ft_strdup(char *s1)
{
	char	*ptr;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
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
