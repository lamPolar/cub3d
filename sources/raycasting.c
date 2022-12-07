#include "cub3d.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length) + x * (img->bits_per_pixel / 8);
	*(unsigned int *) dst = color;
}

int	is_wall_hit(double ray_angle, t_point *now, t_info *info, t_wall *hit)
{
	t_points	*points;
	int			cell;

	points = (t_points *)ft_calloc(sizeof(t_points), 1);
	if (points == NULL)
		return (0);
	init_points(points, now, ray_angle);
	while (1)
	{
		check_hit_point(points, now);
		if (points->dist_vertical < points->dist_horizon)
			calculate_vertical_point(points, hit);
		else
			calculate_horizontal_point(points, hit);
		cell = get_cell(points->map_x, points->map_y, info);
		// if (cell < 0)
		// 	break; // map 밖으로 나감
		if (cell == '1')
		{
			free(points);
			return (1);
		}
		if (hit->side == DIR_W || hit->side == DIR_E)
			points->near_x += points->move_x;
		else
			points->near_y += points->move_y;
	}
	return (0);
}

void	draw_floor_ceiling(t_info *info, t_mlx *mlx)
{
	int	x;
	int	y;

	x = 0;
	while (x < WINDOWW)
	{
		y = 0;
		while (y < WINDOWH)
		{
			if (y < WINDOWH / 2)
				my_mlx_pixel_put(&mlx->img, x, y, info->ceiling);
			else
				my_mlx_pixel_put(&mlx->img, x, y, info->floor);
			y += 1;
		}
		x += 1;
	}
}

int get_wall_height(double dist_wall, t_ray *sight)
{
	int		wall_height;
	double	total_height;
	int		wall_pixel_height;

	wall_height = 1;
	total_height = dist_wall * tan(sight->vertical_angle / 2.0);
	wall_pixel_height = WINDOWH * wall_height / (2.0 * total_height);
	return (wall_pixel_height);
}

void	drawing(t_info *info, t_mlx *mlx)
{
	t_ray	*sight;
	t_point	*now;
	t_wall	*hit;
	int		i;

	sight = NULL;
	init_sight(info->player_char, &sight);
	now = (t_point *)ft_calloc(sizeof(t_point), 1);
	if (now == NULL)
		return ;
	hit = (t_wall *)ft_calloc(sizeof(t_wall), 1);
	if (hit == NULL)
		return ; // 여기서 모든걸 프리하고 종료하는 함수로 이동
	now->x = info->player_x;
	now->y = info->player_y;
	draw_floor_ceiling(info, mlx);
	//draw wall
	i = 0;
	while (i < WINDOWW)
	{
		double ray = get_ray_angle(i, sight);
		// printf("cosign : %f \n", cos(sight->sight_angle - ray));
		if (is_wall_hit(ray, now, info, hit) == 0)
			return ; //null 가드 & 모든걸 프리하고 종료
		double wall_distance = get_distance(now->x, now->y, hit->wx, hit->wy);
		// wall_distance *= cos(sight->sight_angle - ray); 
		// 보정 되면 오히려 반대로 휨..?
		// printf("Wall Distance : %f\n", wall_distance);
		double wall_height = get_wall_height(wall_distance, sight);
		// printf("Wall Height : %f\n", wall_height);
		int ystart = (int)((WINDOWH - wall_height) / 2.0);
	    int yend = ystart + wall_height - 1;
		// printf("%i, %i, %i\n",i, ystart, yend);
		if (0 > y0)
			ystart = 0;
		if (WINDOWH - 1 < yend)
			yend = WINDOWH - 1;
		while (ystart < yend)
		{
			my_mlx_pixel_put(&mlx->img, i, ystart, 0x0000FF00);
			ystart += 1;
		}
		i += 1;
	}
	free(sight);
	free(now);
	free(hit);
}

// static void	load_image(t_info *info, t_img *texture, char *path)
// {
// 	texture->img = mlx_xpm_file_to_image(info->mlx, path, \
// 		&texture->img_width, &texture->img_height);
// 	if (!texture->img)
// 		exit_error("Failed to load image");
// 	texture->data = (char *)mlx_get_data_addr(texture->img, &texture->bpp, \
// 		&texture->size_l, &texture->endian);
// 	if (!texture->data)
// 		exit_error("Failed to create mlx image data");
// }

// void	init_texture(t_info *info)
// {
// 	t_map	*map;
// 	int		i;

// 	map = info->map;
// 	i = 0;
// 	while (i < 4)
// 	{
// 		load_image(info, &(map->texture[i]), map->tex_files[i]);
// 		i++;
// 	}
// }

void do_mlx(t_info *info)
{
    t_mlx	mlx;
	
	init_texture(info);
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WINDOWW, WINDOWH, "cub3D");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WINDOWW, WINDOWH);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bits_per_pixel, \
										&mlx.img.line_length, &mlx.img.endian);
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 5, close_window, &mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	drawing(info, &mlx);
    mlx_loop(mlx.mlx_ptr);
}
