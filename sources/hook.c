#include "cub3d.h"

int	key_hook(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		exit(0);
	}
    // else if (keycode == KEY_W) //move the point of view 
    // {
    
    // }
    // else if (keycode == KEY_A)
    // {

    // }
    // else if (keycode == KEY_S)
    // {

    // }
    // else if (keycode == KEY_D)
    // {

    // }
    // else if (keycode == KEY_LEFT) //look left and right
    // {

    // }
    // else if (keycode == KEY_RIGHT)
    // {

    // }
	return (0);
}

int	close_window(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
}

