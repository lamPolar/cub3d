/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:17:55 by sojoo             #+#    #+#             */
/*   Updated: 2022/12/07 23:18:13 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**ft_free_result(char **result, int total)
{
	int	index;

	index = 0;
	while (index < total)
	{
		free(result[index]);
		index++;
	}
	free(result);
	return (0);
}

static int	ft_check_words(const char *s, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (s[index])
	{
		count++;
		while (s[index] && s[index] != c)
			index++;
		if (s[index])
			index++;
	}
	return (count);
}

static int	ft_count_word_len(const char *s, char c)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	if (s[index] && s[index] == c)
		index++;
	while (s[index] && s[index] != c)
	{
		index++;
		count++;
	}
	return (count);
}

static void	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	index;

	index = 0;
	while (index + 1 < dstsize && src[index])
	{
		dst[index] = src[index];
		index++;
	}
	if (dstsize)
		dst[index] = '\0';
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	char	*word;
	int		index;
	int		count_words;
	int		count_word_len;

	count_words = ft_check_words(s, c);
	result = (char **)ft_calloc(count_words + 1, sizeof(char *));
	if (!result)
		return (0);
	index = 0;
	result[count_words] = 0;
	while (index < count_words)
	{
		count_word_len = ft_count_word_len(s, c);
		word = (char *)ft_calloc(count_word_len + 1, sizeof(char));
		if (!word)
			return (ft_free_result(result, index));
		if (*s && *s == c)
			s++;
		ft_strlcpy(word, s, count_word_len + 1);
		s += count_word_len;
		result[index++] = word;
	}
	return (result);
}
