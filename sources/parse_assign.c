/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_assign.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:28:21 by sojoo             #+#    #+#             */
/*   Updated: 2022/12/07 23:24:48 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	assign_info(int type, char *line, int fd, t_info *info)
{
	int	i;

	if (type >= 0 && type <= 3)
		assign_tex(type, line, fd, info);
	else if (type == 4 || type == 5)
		assign_color(type, line, fd, info);
	else
	{
		i = ft_strlen(line);
		if (info->map_width < i)
			info->map_width = i;
		if (info->map_temp == NULL)
			info->map_temp = ft_strdup(line);
		else
			info->map_temp = ft_strjoin(info->map_temp, line);
		if (info->map_temp == NULL)
			error_in_parsing(line, "Failed to allocate memory\n", fd, info);
	}
}

void	assign_tex(int type, char *line, int fd, t_info *info)
{
	int	i;
	int	j;
	int	len;

	if (info->tex[type] != NULL)
		error_in_parsing(line, "Duplicate texture information\n", fd, info);
	i = 2;
	len = 0;
	while (line[i] == ' ')
		i++;
	while (line[i++] != '\n')
		len++;
	info->tex[type] = (char *)calloc(len + 1, sizeof(char));
	if (info->tex[type] == NULL)
		error_in_parsing(line, "Failed to allocate memory\n", fd, info);
	i -= len + 1;
	j = 0;
	while (j < len)
		info->tex[type][j++] = line[i++];
	info->tex[type][j] = '\0';
}

void	assign_color(int type, char *line, int fd, t_info *info)
{
	int		i;
	int		len;
	char	*str;
	char	**split;

	if ((type == 4 && info->floor != -1) || (type == 5 && info->ceiling != -1))
		error_in_parsing(line, "Duplicate color information\n", fd, info);
	i = 1;
	len = 0;
	while (line[i] == ' ')
		i++;
	while (line[i++] != '\n')
		len++;
	str = ft_substr(line, i - len - 1, len);
	split = ft_split(str, ',');
	free(str);
	i = create_color(split);
	if (i == -1)
		error_in_parsing(line, "Invalid color information\n", fd, info);
	if (type == 4)
		info->floor = i;
	else if (type == 5)
		info->ceiling = i;
}

int	create_color(char **split)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	while (split[i])
		i++;
	if (i != 3)
	{
		free_split(split);
		return (-1);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free_split(split);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		return (-1);
	return ((r << 16) + (g << 8) + b);
}
