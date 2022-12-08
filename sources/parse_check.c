/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:32:54 by sojoo             #+#    #+#             */
/*   Updated: 2022/12/08 19:34:47 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_player(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (info->map[i][j] == 'N' || info->map[i][j] == 'S' || \
				info->map[i][j] == 'E' || info->map[i][j] == 'W')
			{
				if (info->player_char != 0)
					return (0);
				info->player_char = info->map[i][j];
				info->player_x = (double)j + 0.5;
				info->player_y = (double)i + 0.5;
			}
			j++;
		}
		i++;
	}
	if (info->player_char == 0)
		return (0);
	return (1);
}

int	check_map(t_info *info)
{
	if (check_first_line(info) == 0)
		return (0);
	if (check_middle_line(info) == 0)
		return (0);
	if (check_last_line(info) == 0)
		return (0);
	return (1);
}

int	check_edge(char *line)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] == ' ')
		i++;
	j = ft_strlen(line) - 1;
	while (line[j] == ' ')
		j--;
	if (line[i] != '1' || line[j] != '1')
		return (0);
	return (1);
}
