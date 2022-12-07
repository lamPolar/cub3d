/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 03:15:28 by heeskim           #+#    #+#             */
/*   Updated: 2022/12/08 03:15:31 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall_hit(double ray_angle, t_point *now, t_info *info, t_wall *hit)
{
	t_points	*points;
	int			cell;

	points = (t_points *)ft_calloc(sizeof(t_points), 1);
	if (points == NULL)
		return (0);
	init_points(points, now, ray_angle);
	while (1)
	{
		check_hit_point(points, now);
		if (points->dist_vertical < points->dist_horizon)
			calculate_vertical_point(points, hit);
		else
			calculate_horizontal_point(points, hit);
		cell = get_cell(points->map_x, points->map_y, info);
		// if (cell < 0)
		// 	break; // map 밖으로 나감
		if (cell == '1')
		{
			free(points);
			return (1);
		}
		if (hit->side == DIR_W || hit->side == DIR_E)
			points->near_x += points->move_x;
		else
			points->near_y += points->move_y;
	}
	return (0);
}

int get_wall_height(double dist_wall, t_ray *sight)
{
	int		wall_height;
	int		wall_pixel_height;
	double	total_height;

	wall_height = 1;
	total_height = dist_wall * tan(sight->vertical_angle / 2.0);
	wall_pixel_height = WINDOWH * wall_height / (2.0 * total_height);
	return (wall_pixel_height);
}

void	draw_wall(t_info *info, t_point *now, t_wall *hit)
{
	double	wall_distance;
	double	wall_height;
	int		ystart;
	int		yend;
	int		i;
	double	ray;

	i = 0;
	while (i < WINDOWW)
	{
		ray = get_ray_angle(i, info->ray);
		if (is_wall_hit(ray, now, info, hit) == 0)
			return ; //null 가드 & 모든걸 프리하고 종료
		wall_distance = get_distance(now->x, now->y, hit->wx, hit->wy);
		wall_distance *= cos(info->ray->sight_angle - ray);
		wall_height = get_wall_height(wall_distance, info->ray);
		ystart = (int)((WINDOWH - wall_height) / 2.0);
	    yend = ystart + wall_height - 1;
		if (0 > ystart)
			ystart = 0;
		if (WINDOWH - 1 < yend)
			yend = WINDOWH - 1;
		while (ystart < yend)
		{
			my_mlx_pixel_put(&info->mlx->img, WINDOWW - i, ystart, 0x0000FF00);
			ystart += 1;
		}
		i += 1;
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
		return ;
	hit = (t_wall *)ft_calloc(sizeof(t_wall), 1);
	if (hit == NULL)
		return ; // 여기서 모든걸 프리하고 종료하는 함수로 이동
	now->x = info->player_x;
	now->y = info->player_y;
	draw_floor_ceiling(info);
	draw_wall(info, now, hit);
	free(now);
	free(hit);
}
