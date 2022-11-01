/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:18:16 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/03 03:27:30 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*saved;

	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved)
	{
		saved = gnl_calloc(1, sizeof(char));
		if (!saved)
			return (NULL);
	}
	return (gnl_makeresult(fd, &saved));
}

char	*gnl_readline(int fd, char **saved)
{
	char	*buf;
	int		rbyte;

	buf = (char *)gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (gnl_free(saved, buf));
	rbyte = read(fd, buf, BUFFER_SIZE);
	if (rbyte <= 0)
		return (gnl_free(saved, buf));
	*saved = gnl_strjoin(*saved, buf);
	if (!*saved)
		return (0);
	return (gnl_makeresult(fd, saved));
}

char	*gnl_free(char **saved, char *buf)
{
	char	*result;
	int		len;

	result = NULL;
	if (*saved)
	{
		len = 0;
		while ((*saved)[len])
			len++;
		if (len > 0)
		{
			result = gnl_calloc(sizeof(char), len);
			if (!result)
				return (NULL);
			gnl_strcpy(result, *saved, len + 1);
			len = 0;
			while ((*saved)[len])
				(*saved)[len++] = 0;
		}
		free(*saved);
		*saved = NULL;
	}
	if (buf)
		free(buf);
	return (result);
}

int	gnl_isnl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
}

char	*gnl_makeresult(int fd, char	**saved)
{
	int		nl;
	char	*result;

	if (!**saved)
		return (gnl_readline(fd, saved));
	nl = gnl_isnl(*saved);
	if (nl == -1)
		return (gnl_readline(fd, saved));
	result = gnl_strcut(*saved, nl);
	if (!result)
		return (0);
	gnl_strmove(*saved, nl);
	return (result);
}
