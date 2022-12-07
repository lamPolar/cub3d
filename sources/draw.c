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
		if (get_cell(points->map_x, points->map_y, info) == '1')
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

int	get_wall_height(double dist_wall, t_ray *sight)
{
	int		wall_height;
	int		wall_pixel_height;
	double	total_height;

	wall_height = 1;
	total_height = dist_wall * tan(sight->vertical_angle / 2.0);
	wall_pixel_height = WINDOWH * wall_height / (2.0 * total_height);
	return (wall_pixel_height);
}

int get_tex_color(t_wall *hit, int text_x, int text_y, t_info *info)
{
	t_img	*src;
	int		color;

	if (hit->side == DIR_N)
		src = info->mlx->tex[0];
	if (hit->side == DIR_S)
		src = info->mlx->tex[1];
	if (hit->side == DIR_W)
		src = info->mlx->tex[2];
	if (hit->side == DIR_E)
		src = info->mlx->tex[3];
	color = *(unsigned int *)(src->img_ptr + text_y * src->line_length \
			+ text_x * src->bits_per_pixel / 8);
	return (color);
}

void	draw_wall(t_info *info, t_point *now, t_wall *hit)
{
	double	wall_distance;
	double	wall_height;
	int		ystart;
	int		yend;
	int		x;
	double	ray;

	x = 0;
	while (x < WINDOWW)
	{
		ray = get_ray_angle(x, info->ray);
		if (is_wall_hit(ray, now, info, hit) == 0)
			return ;//null 가드 & 모든걸 프리하고 종료
		wall_distance = get_distance(now->x, now->y, hit->wx, hit->wy);
		wall_distance *= cos(info->ray->sight_angle - ray);
		wall_height = get_wall_height(wall_distance, info->ray);
		ystart = (int)((WINDOWH - wall_height) / 2.0);
		yend = ystart + wall_height - 1;
		if (0 > ystart)
			ystart = 0;
		if (WINDOWH - 1 < yend)
			yend = WINDOWH - 1;
		// //가로축에 맞았을 경우
		// int text_x;
		// int text_y;
		// if (hit->side == DIR_N || hit->side == DIR_S)
		// 	text_x = (int)fmod(hit->wx, 1) * 100;
		// //x 에 대해서 상대적인 텍스쳐 x의값 구하기
		// else
		// 	text_x = (int)fmod(hit->wy, 1) * 100;
		// //세로축에 맞았을 경우
		// //y 에 대해서 상대적인 텍스쳐 x값 구하기
		// while (ystart < yend)
		// {
		// 	text_y = (ystart - (WINDOWH/ 2 - wall_height)) * 100 / wall_height;
		// 	//y 에 대해서 상대적인 텍스쳐의 y의 값 구하기
		// 	//상대적인 텍스쳐의 x, y값에 해당하는 텍스쳐의 값 가져오기
		// 	t_img *dst;

		// 	dst = &info->mlx->img;
		// 	*(unsigned int *)(dst->img_ptr + ystart * dst->line_length + x * dst->bits_per_pixel / 8) = get_tex_color(hit, text_x, text_y, info);
		// 	// my_mlx_pixel_put(&info->mlx->img, WINDOWW - x, ystart, get_tex_color(hit, text_x, text_y, info));
		// 	ystart += 1;
		// }
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
		return ;
	hit = (t_wall *)ft_calloc(sizeof(t_wall), 1);
	if (hit == NULL)
		return ;// 여기서 모든걸 프리하고 종료하는 함수로 이동
	now->x = info->player_x;
	now->y = info->player_y;
	draw_floor_ceiling(info);
	draw_wall(info, now, hit);
	free(now);
	free(hit);
}
