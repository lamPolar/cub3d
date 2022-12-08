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
	double dx;
	double dy;
	int cell;

	dx = 0;
	dy = 0;
	if (keycode == KEY_W)
	{
		dx = 0.2 * cos(info->ray->sight_angle);
		dy = 0.2 * sin(info->ray->sight_angle);
	}
	else if (keycode == KEY_A)
	{
		dx = 0.2 * cos(info->ray->sight_angle - M_PI_2);
		dy = 0.2 * sin(info->ray->sight_angle - M_PI_2);
	}
	else if (keycode == KEY_S)
	{
		dx = -0.2 * cos(info->ray->sight_angle);
		dy = -0.2 * sin(info->ray->sight_angle);
	}
	else if (keycode == KEY_D)
	{
		dx = 0.2 * cos(info->ray->sight_angle + M_PI_2);
		dy = 0.2 * sin(info->ray->sight_angle + M_PI_2);
	}
	printf("player : %f, %f delta : %f, %f\n", info->player_x, info->player_y, dx, dy);
	printf("cell : %c\n", get_cell((int)info->player_x + dx, (int)info->player_y + dy, info));
	//이동할 곳이 벽을 뚫고 가진 않았는지 확인하기
	//이동하는곳을 보는 위치가 왼쪽, 아래에서 접근할 때랑 오른쪽, 위에서 접근할 때랑 측정 범위가 달라서 
	// 오른쪽, 위에서 접근하면 훨씬 멀리부터 벽이라고 인지함
	cell = get_cell((int)info->player_x + dx, (int)info->player_y + dy, info);
	if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
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
	else if (keycode == KEY_W || keycode == KEY_A \
			|| keycode == KEY_S || keycode == KEY_D)
		moving(keycode, info);
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
