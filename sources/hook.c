#include "cub3d.h"

int	key_hook(int keycode, t_info *info)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(info->mlx->mlx_ptr, info->mlx->win_ptr);
		exit(0);
	}
    else if (keycode == KEY_W) //move the point of view 
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
    else if (keycode == KEY_LEFT) //look left and right
    {
        info->ray->sight_angle -= 0.1;
    }
    else if (keycode == KEY_RIGHT)
    {
        info->ray->sight_angle += 0.1;
    }
    mlx_clear_window(info->mlx->mlx_ptr, info->mlx->win_ptr);
    drawing(info);
   	mlx_put_image_to_window(info->mlx->mlx_ptr, info->mlx->win_ptr, info->mlx->img.img_ptr, 0, 0);
	return (0);
}

int	close_window(t_info *info)
{
	mlx_destroy_window(info->mlx->mlx_ptr, info->mlx->win_ptr);
	exit(0);
}

