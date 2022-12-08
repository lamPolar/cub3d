/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 03:15:48 by heeskim           #+#    #+#             */
/*   Updated: 2022/12/08 11:56:36 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length) + x * (img->bits_per_pixel / 8);
	*(unsigned int *) dst = color;
}

unsigned int	my_mlx_get_color(t_img *img, int x, int y)
{
	unsigned int	data;

	data = *(unsigned int *)(img->addr + (img->line_length * y) + \
		(img->bits_per_pixel / 8) * x);
	return (data);
}

void	init_texture(t_info *info)
{
	int		i;
	int		size;
	t_img	*tex;

	i = 0;
	size = TEXTURE_SIZE;
	while (i < 4)
	{
		tex = &info->mlx->tex[i];
		tex->img_ptr = mlx_xpm_file_to_image(info->mlx->mlx_ptr, \
											info->tex[i], &size, &size);
		if (tex->img_ptr == NULL)
		{
			printf("Error\nNo texture file\n");
			return ;
		}
		tex->addr = (char *)mlx_get_data_addr(tex->img_ptr, \
				&(tex->bits_per_pixel), &(tex->line_length), &(tex->endian));
		if (tex->addr == NULL)
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
	mlx->mlx_ptr = mlx_init();
	init_texture(info);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WINDOWW, WINDOWH, "cub3D");
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WINDOWW, WINDOWH);
	if (mlx->img.img_ptr == NULL)
		printf("Error");
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr, \
					&mlx->img.bits_per_pixel, &mlx->img.line_length, \
					&mlx->img.endian);
	if (mlx->img.addr == NULL)
		printf("Error");
	mlx_key_hook(mlx->win_ptr, key_hook, info);
	mlx_hook(mlx->win_ptr, 17, 1L << 5, close_window, info);
	drawing(info);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, \
							mlx->img.img_ptr, 0, 0);
	mlx_loop(mlx->mlx_ptr);
}
