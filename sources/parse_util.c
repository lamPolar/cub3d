/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 23:33:01 by sojoo             #+#    #+#             */
/*   Updated: 2022/12/08 14:13:18 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_info	*init_info(void)
{
	t_info	*info;

	info = (t_info *)ft_calloc(1, sizeof(t_info));
	if (info == NULL)
		exit(1);
	info->tex = (char **)ft_calloc(4, sizeof(char *));
	if (info->tex == NULL)
	{
		free(info);
		exit(1);
	}
	info->mlx = (t_mlx *)ft_calloc(sizeof(t_mlx), 1);
	info->ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (info->mlx == NULL | info->ray == NULL)
		print_error_free_info("Error\nFailed to allocate memory\n", info);
	info->floor = -1;
	info->ceiling = -1;
	info->map_temp = NULL;
	info->map = NULL;
	info->map_width = 0;
	info->map_height = 0;
	info->player_char = 0;
	info->player_x = 0;
	info->player_y = 0;
	return (info);
}

void	error_in_parsing(char *line, char *str, int fd, t_info *info)
{
	free(line);
	close(fd);
	print_error_free_info(str, info);
}

void	print_error_free_info(char *str, t_info *info)
{
	int	i;

	printf("%s", str);
	if (info->tex)
	{
		i = 0;
		while (i < 4)
		{
			if (info->tex[i] != NULL)
				free(info->tex[i]);
			i++;
		}
		free(info->tex);
	}
	if (info->map_temp != NULL)
		free(info->map_temp);
	if (info->map)
		free_split(info->map);
	if (info->mlx)
		free(info->mlx);
	if (info->ray)
		free(info->ray);
	free(info);
	exit(1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
