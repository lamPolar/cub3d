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

void	do_mlx(t_info *info)
{
    t_mlx	*mlx;
	
	mlx = info->mlx;
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WINDOWW, WINDOWH, "cub3D");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WINDOWW, WINDOWH);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bits_per_pixel, \
										&mlx->img.line_length, &mlx->img.endian);
	mlx_key_hook(mlx->win_ptr, key_hook, info);
	mlx_hook(mlx->win_ptr, 17, 1L << 5, close_window, info);
	drawing(info);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
    mlx_loop(mlx->mlx_ptr);
}
