/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 15:10:36 by sojoo             #+#    #+#             */
/*   Updated: 2022/12/07 20:18:38 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(const char *s)
{
	int	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[count])
		count += 1;
	return (count);
}

void	*ft_calloc(size_t count, size_t size)
{
	void			*new;
	size_t			index;
	unsigned char	*ptr;

	new = (void *)malloc(count * size);
	if (new == NULL)
		return (NULL);
	index = 0;
	ptr = (unsigned char *)new;
	while (index < count * size)
	{	
		ptr[index] = '\0';
		index += 1;
	}
	return (new);
}

int	ft_atoi(const char *str)
{
	long long	result;
	long long	tmp;
	long long	sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tmp = result;
		result = result * 10 + (*str - '0');
		if (tmp > result && sign < 0)
			return (0);
		if (tmp > result && sign > 0)
			return (-1);
		str++;
	}
	return ((int)(result * sign));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (n > 0)
	{
		if (*c1 == *c2 && *c1 != '\0')
		{
			c1++;
			c2++;
			n--;
		}
		else
			return (*c1 - *c2);
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	slen;
	size_t	index;
	
	slen = ft_strlen(s);
	if (len > slen)
		new = (char *)ft_calloc(slen + 1, sizeof(char));
	else
		new = (char *)ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (0);
	if (start <= (unsigned int)slen)
	{
		index = 0;
		s += start;
		while (index + 1 < len + 1 && s[index])
		{
			new[index] = s[index];
			index++;
		}
		if (len + 1)
			new[index] = '\0';
	}
	return (new);
}

char    *ft_strjoin(char *s1, char *s2)
{
    char    *str;
    size_t  len;
    size_t  i;
    if (!s1 || !s2)
        return (0);
    if (*s1 == '\0' && *s2 == '\0')
        len = 1;
    else
        len = ft_strlen(s1) + ft_strlen(s2) + 1;
    str = (char *)ft_calloc(sizeof(char), len);
    if (!str)
        return (0);
    i = -1;
    while (s1[++i] != '\0')
        str[i] = s1[i];
    len = 0;
    while (s2[len] != '\0')
        str[i++] = s2[len++];
    free(s1);
    return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*new;
	size_t	slen;
	
	slen = ft_strlen(s1);
	new = (char *)malloc(sizeof(char) * (slen + 1));
	if (!new)
		return (0);
	while (slen > 0)
	{	
		new[slen] = s1[slen];
		slen--;
	}
	new[0] = s1[0];
	return (new);
}
