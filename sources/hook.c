/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 03:15:20 by heeskim           #+#    #+#             */
/*   Updated: 2022/12/08 11:55:47 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	moving_ws(int keycode, t_info *info)
{
	double	dx;
	double	dy;
	int		cell;

	dx = 0;
	dy = 0;
	if (keycode == KEY_W)
	{
		dx = 0.2 * cos(info->ray->sight_angle);
		dy = 0.2 * sin(info->ray->sight_angle);
	}
	else if (keycode == KEY_S)
	{
		dx = -0.2 * cos(info->ray->sight_angle);
		dy = -0.2 * sin(info->ray->sight_angle);
	}
	cell = get_cell((int)info->player_x + dx, (int)info->player_y + dy, info);
	if (cell == '0' || cell == info->player_char)
	{
		info->player_x += dx;
		info->player_y += dy;
	}
}

void	moving_ad(int keycode, t_info *info)
{
	double	dx;
	double	dy;
	int		cell;

	dx = 0;
	dy = 0;
	if (keycode == KEY_A)
	{
		dx = 0.2 * cos(info->ray->sight_angle - M_PI_2);
		dy = 0.2 * sin(info->ray->sight_angle - M_PI_2);
	}
	else if (keycode == KEY_D)
	{
		dx = 0.2 * cos(info->ray->sight_angle + M_PI_2);
		dy = 0.2 * sin(info->ray->sight_angle + M_PI_2);
	}
	cell = get_cell((int)info->player_x + dx, (int)info->player_y + dy, info);
	if (cell == '0' || cell == info->player_char)
	{
		info->player_x += dx;
		info->player_y += dy;
	}
}

int	key_hook(int keycode, t_info *info)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(info->mlx->mlx_ptr, info->mlx->win_ptr);
		exit(0);
	}
	else if (keycode == KEY_W || keycode == KEY_S)
		moving_ws(keycode, info);
	else if (keycode == KEY_A || keycode == KEY_D)
		moving_ad(keycode, info);
	else if (keycode == KEY_LEFT)
		info->ray->sight_angle -= 0.1;
	else if (keycode == KEY_RIGHT)
		info->ray->sight_angle += 0.1;
	if (info->ray->sight_angle < 0)
		info->ray->sight_angle += 2 * M_PI;
	else if (info->ray->sight_angle > 2 * M_PI)
		info->ray->sight_angle -= 2 * M_PI;
	mlx_clear_window(info->mlx->mlx_ptr, info->mlx->win_ptr);
	drawing(info);
	mlx_put_image_to_window(info->mlx->mlx_ptr, info->mlx->win_ptr, \
							info->mlx->img.img_ptr, 0, 0);
	return (0);
}

int	close_window(t_info *info)
{
	mlx_destroy_window(info->mlx->mlx_ptr, info->mlx->win_ptr);
	exit(0);
}
