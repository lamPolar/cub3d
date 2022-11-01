/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 19:18:28 by heeskim           #+#    #+#             */
/*   Updated: 2022/09/03 03:12:46 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_strmove(char *saved, int len)
{
	int	i;

	i = 0;
	while (saved[i + len])
	{
		saved[i] = saved[i + len];
		i++;
	}
	saved[i] = '\0';
}

void	*gnl_calloc(size_t count, size_t size)
{
	void			*new;
	size_t			index;
	unsigned char	*ptr;

	new = (void *)malloc(count * size);
	if (!new)
		return (0);
	index = 0;
	ptr = (unsigned char *)new;
	while (index < count * size)
		ptr[index++] = '\0';
	return (new);
}

void	gnl_strcpy(char *dst, const char *src, int len)
{
	int	index;

	index = 0;
	while (src[index] && index + 1 < len)
	{
		dst[index] = src[index];
		index++;
	}
	dst[index] = '\0';
}

char	*gnl_strcut(char const *saved, int nl)
{
	char	*new;

	new = (char *)gnl_calloc(nl + 1, sizeof(char));
	if (!new)
		return (0);
	gnl_strcpy(new, saved, nl + 1);
	return (new);
}

char	*gnl_strjoin(char *saved, char *buf)
{
	size_t	len1;
	size_t	len2;
	char	*new;

	len1 = 0;
	len2 = 0;
	while (saved[len1])
		len1++;
	while (buf[len2])
		len2++;
	new = (char *)gnl_calloc(len1 + len2 + 1, sizeof(char));
	if (!new)
		return (0);
	gnl_strcpy(new, saved, len1 + 1);
	gnl_strcpy(new + len1, buf, len2 + 1);
	free(buf);
	free(saved);
	saved = NULL;
	return (new);
}
