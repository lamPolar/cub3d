/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 03:15:28 by heeskim           #+#    #+#             */
/*   Updated: 2022/12/08 14:19:08 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_wall_hit(double ray_angle, t_point *now, t_info *info, t_wall *hit)
{
	t_points	*points;

	points = (t_points *)ft_calloc(sizeof(t_points), 1);
	if (points == NULL)
		print_error_free_info("Error\nFailed to allocate memory\n", info);
	init_points(points, now, ray_angle);
	while (1)
	{
		check_hit_point(points, now);
		if (points->dist_vertical < points->dist_horizon)
			calculate_vertical_point(points, hit);
		else
			calculate_horizontal_point(points, hit);
		if (get_cell(points->map_x, points->map_y, info) == '1')
		{
			free(points);
			return ;
		}
		if (hit->side == DIR_W || hit->side == DIR_E)
			points->near_x += points->move_x;
		else
			points->near_y += points->move_y;
	}
}

void	fill_tex_color(t_info *info, t_wall *hit, int x, double wall_height)
{
	int				ystart;
	int				yend;
	int				text_x;
	int				text_y;
	unsigned int	color;

	ystart = (int)((WINDOWH - wall_height) / 2.0);
	yend = ystart + wall_height - 1;
	if (0 > ystart)
		ystart = 0;
	if (WINDOWH - 1 < yend)
		yend = WINDOWH - 1;
	if (hit->side == DIR_N || hit->side == DIR_S)
		text_x = fmod(hit->wx, 1) * TEXTURE_SIZE;
	else
		text_x = fmod(hit->wy, 1) * TEXTURE_SIZE;
	while (ystart < yend)
	{
		text_y = (ystart - (WINDOWH / 2 - wall_height)) * \
			TEXTURE_SIZE / wall_height;
		color = my_mlx_get_color(&info->mlx->tex[hit->side - 20], \
			text_x, text_y);
		my_mlx_pixel_put(&info->mlx->img, WINDOWW - x, ystart, color);
		ystart += 1;
	}
}

void	draw_wall(t_info *info, t_point *now, t_wall *hit)
{
	double	wall_distance;
	double	wall_height;
	int		x;
	double	ray;

	x = 0;
	while (x < WINDOWW)
	{
		ray = get_ray_angle(x, info->ray);
		is_wall_hit(ray, now, info, hit);
		wall_distance = get_distance(now->x, now->y, hit->wx, hit->wy);
		wall_distance *= cos(info->ray->sight_angle - ray);
		wall_height = get_wall_height(wall_distance, info->ray);
		fill_tex_color(info, hit, x, wall_height);
		x += 1;
	}
}

void	draw_floor_ceiling(t_info *info)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOWW)
	{
		y = 0;
		while (y < WINDOWH)
		{
			if (y < WINDOWH / 2)
				my_mlx_pixel_put(&info->mlx->img, x, y, info->ceiling);
			else
				my_mlx_pixel_put(&info->mlx->img, x, y, info->floor);
			y += 1;
		}
		x += 1;
	}
}

void	drawing(t_info *info)
{
	t_point	*now;
	t_wall	*hit;

	now = (t_point *)ft_calloc(sizeof(t_point), 1);
	if (now == NULL)
		print_error_free_info("Error\nFailed to allocate memory\n", info);
	hit = (t_wall *)ft_calloc(sizeof(t_wall), 1);
	if (hit == NULL)
	{
		free(now);
		print_error_free_info("Error\nFailed to allocate memory\n", info);
	}
	now->x = info->player_x;
	now->y = info->player_y;
	draw_floor_ceiling(info);
	draw_wall(info, now, hit);
	free(now);
	free(hit);
}
