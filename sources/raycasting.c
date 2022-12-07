#include "cub3d.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img -> line_length + x *( img->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}


int	is_wall_hit(double ray_angle, t_point *now, t_info *info, t_wall *hit)
{
	t_points	*points;
	int 		cell;
	
	points = (t_points *)ft_calloc(sizeof(t_points), 1);
	if (points == NULL)
		return (0); // 여기서 뭘 보내주지?
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
		if (cell == 1)
		{
			free(points);
			return (1);
		}
		continue;
	}
}

void	draw_floor_ceiling(t_info *info, t_mlx *mlx)
{
	int		x;
	int		y;

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
	total_height = dist_wall * tan(sight->vertical_angle/2.0);
	wall_pixel_height = WINDOWH * wall_height / (2.0 * total_height);
	return (wall_pixel_height);
}

void drawing(t_info *info, t_mlx *mlx)
{
	t_ray	*sight;
	t_point	*now;
	t_wall	*hit;
	int		i;

	sight = NULL;
	init_sight(&sight);
	printf("sight : %d\n" ,sight->total_ray);
	now = (t_point *)ft_calloc(sizeof(t_point), 1);
	if (now == NULL)
		return ;
	hit = (t_wall *)ft_calloc(sizeof(t_wall), 1);
	if (hit == NULL)
		return ; // 여기서 모든걸 프리하고 종료하는 함수로 이동
	// player를 t_point로 만들면 now = info->player;
	//now->x = info->player_x;
	//now->y = info->player_y;
	now->x = 0.5;
	now->y = 0.5;
	draw_floor_ceiling(info, mlx);
	//draw wall
	i = 0;
	while (i < sight->total_ray)
	{
		if (is_wall_hit(get_ray_angle(i, sight), now, info, hit) == 0)
			return ; //null 가드 & 모든걸 프리하고 종료
		double wall_distance = get_distance(now->x, now->y, hit->wx, hit->wy);
		printf("Wall Distance : %f", wall_distance);
		double wall_height = get_wall_height(wall_distance, sight);
		printf("Wall Height : %f", wall_height);
		i += 1;
	}
	free(sight);
	free(now);
	free(hit);
}

void do_mlx(t_info *info)
{
    t_mlx	mlx;
	
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WINDOWW, WINDOWH, "cub3D");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WINDOWW, WINDOWH);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bits_per_pixel, \
										&mlx.img.line_length, &mlx.img.endian);
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 5, close_window, &mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	info->ceiling =  0x00FF0000;
	info->floor = 0x0000FF00;
	drawing(info, &mlx);
    mlx_loop(mlx.mlx_ptr);
}
