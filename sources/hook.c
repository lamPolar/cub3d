/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 03:15:20 by heeskim           #+#    #+#             */
/*   Updated: 2022/12/08 03:15:22 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	moving(int keycode, t_info *info)
{
	if (keycode == KEY_W)
	{
		info->player_x += 0.2 * cos(info->ray->sight_angle);
		info->player_y += 0.2 * sin(info->ray->sight_angle);
	}
	else if (keycode == KEY_A)
	{
		info->player_x -= 0.2 * cos(info->ray->sight_angle);
		info->player_y += 0.2 * sin(info->ray->sight_angle);
	}
	else if (keycode == KEY_S)
	{
		info->player_x += 0.2 * cos(info->ray->sight_angle);
		info->player_y -= 0.2 * sin(info->ray->sight_angle);
	}
	else if (keycode == KEY_D)
	{
		info->player_x -= 0.2 * cos(info->ray->sight_angle);
		info->player_y -= 0.2 * sin(info->ray->sight_angle);
	}
}

int	key_hook(int keycode, t_info *info)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(info->mlx->mlx_ptr, info->mlx->win_ptr);
		exit(0);
	}
	else if (keycode == KEY_W || keycode == KEY_A \
			|| keycode == KEY_S || keycode == KEY_D)
		moving(keycode, info);
	else if (keycode == KEY_LEFT)
		info->ray->sight_angle -= 0.1;
	else if (keycode == KEY_RIGHT)
		info->ray->sight_angle += 0.1;
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
