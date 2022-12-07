/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:27:00 by sojoo             #+#    #+#             */
/*   Updated: 2022/12/07 23:26:10 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_gnl(int fd, t_info *info)
{
	char	*line;
	int		type;
	int		start_map;

	start_map = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!(*line == '\n' && start_map == 0))
		{
			type = check_line_type(line);
			if (type == 6)
			{
				start_map = 1;
				info->map_height += 1;
			}
			else if (type == -1)
				error_in_parsing(line, "Invalid map information\n", fd, info);
			assign_info(type, line, fd, info);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	check_line_type(char *line)
{
	if (line[0] == 'N' && line[1] == 'O')
		return (0);
	else if (line[0] == 'S' && line[1] == 'O')
		return (1);
	else if (line[0] == 'W' && line[1] == 'E')
		return (2);
	else if (line[0] == 'E' && line[1] == 'A')
		return (3);
	else if (line[0] == 'F' && line[1] == ' ')
		return (4);
	else if (line[0] == 'C' && line[1] == ' ')
		return (5);
	else if (check_map_line(line))
		return (6);
	else
		return (-1);
}

int	check_map_line(char *line)
{
	while (*line != '\n' && *line != '\0')
	{
		if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S' \
			&& *line != 'E' && *line != 'W' && *line != ' ')
			return (0);
		line++;
	}
	return (1);
}
