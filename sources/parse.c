/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:36:43 by sojoo             #+#    #+#             */
/*   Updated: 2022/12/08 11:51:40 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_file(int argc, char **argv, t_info *info)
{
	int	fd;

	if (argc != 2)
		print_error_free_info("Please put only one file\n", info);
	if (ft_strncmp(".cub", argv[1] + (ft_strlen(argv[1]) - 4), 4) != 0)
		print_error_free_info("Input file is not .cub file\n", info);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		print_error_free_info("Failed to open file\n", info);
	return (fd);
}

void	parsing(int fd, t_info *info)
{
	check_gnl(fd, info);
	info->map = ft_split(info->map_temp, '\n');
	if (info->map == NULL)
		print_error_free_info("Failed to allocate memory\n", info);
	while (info->map[info->map_height - 1][0] == '\0')
		info->map_height--;
	if (check_player(info) == 0 || check_map(info) == 0)
		print_error_free_info("Invalid map\n", info);
	free(info->map_temp);
}
