#include "cub3d.h"

void do_mlx(void)
{
    t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WINDOWW, WINDOWH, "Cub3d");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WINDOWW, WINDOWH);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bits_per_pixel, \
										&mlx.img.line_length, &mlx.img.endian);
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 5, close_window, &mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
}
