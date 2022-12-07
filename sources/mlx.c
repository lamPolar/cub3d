/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 03:15:48 by heeskim           #+#    #+#             */
/*   Updated: 2022/12/08 03:15:51 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length) + x * (img->bits_per_pixel / 8);
	*(unsigned int *) dst = color;
}

static void init_texture(t_info *info)
{
	int		i;
	int		size;
	t_img	tex;

	i = 0;
	size = 100;
	while (i < 4)
	{
		tex = info->mlx->tex[i];
		// printf("info->tex[i] : \'%s\'\n", info->tex[i]);
		tex.img_ptr = mlx_xpm_file_to_image(info->mlx->mlx_ptr, \
											info->tex[i], &size, &size); 
		//파일을 못찾으면 seg fault가 나는거같은데..?
		// tex.img_ptr== null 에러에 걸려서 프린트됨 
		if (tex.img_ptr == NULL)
		{
			printf("Error\nNo texture file\n");
			return ;
		}
		tex.addr = (char *)mlx_get_data_addr(tex.img_ptr, \
				&(tex.bits_per_pixel), &(tex.line_length), &(tex.endian));
		if (tex.addr == NULL)
		{
			printf("Error\n");
			return ;
		}
		i++;
	}
}

void	do_mlx(t_info *info)
{
	t_mlx	*mlx;

	mlx = info->mlx;
	init_texture(info);
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WINDOWW, WINDOWH, "cub3D");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WINDOWW, WINDOWH);
	if (mlx->img.img_ptr == NULL)
        printf("Error"); //메세지 + 모두 프리
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
					&mlx->img.bits_per_pixel, &mlx->img.line_length, \
					&mlx->img.endian);
	if (mlx->img.addr == NULL)
        printf("Error"); // message + 모두 프리
	mlx_key_hook(mlx->win_ptr, key_hook, info);
	mlx_hook(mlx->win_ptr, 17, 1L << 5, close_window, info);
	drawing(info);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
							mlx->img.img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}
