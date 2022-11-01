#include "cub3d.h"

void my_mlx_pixel_put(t_img *data, int x, int y, int color){
	char *dst;

	dst = data->addr + (y * data -> line_length + x *( data->bits_per_pixel / 8));
	//괄호 = offset
	*(unsigned int *) dst = color;
}

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
    for(int i = 0; i < 100 ; i++) {
	my_mlx_pixel_put(&mlx.img, i, i, 0x00FF0000);// 붉은색 선을 대각선으로 그린다.
	my_mlx_pixel_put(&mlx.img, 5, i, 0x00FF0000);// 붉은색 선을 세로으로 그린다.
	my_mlx_pixel_put(&mlx.img, i, 5, 0x00FF0000);// 붉은색 선을 가로으로 그린다.
	}
	mlx_loop(mlx.mlx_ptr);
}

