#include "cub3d.h"

void my_mlx_pixel_put(t_img *data, int x, int y, int color){
	char *dst;

	dst = data->addr + (y * data -> line_length + x *( data->bits_per_pixel / 8));
	//괄호 = offset
	*(unsigned int *) dst = color;
}

void	init_sight(t_ray *sight)
{
	float angle;

	sight->horizontal_angle = 60;
	if (WINDOWH != 0 && WINDOWW != 0 && sight->horizontal_angle != 0)
	{
		angle = sight->horizontal_angle / WINDOWW * WINDOWH;
		sight->vertical_angle = angle;
	}
	sight->total_ray = 20;
	sight->sight_angle = 1;
	//여기서 sight_angle을 바라보는 방향에 따라 바꿔주기 (N,S,W,E)
}

double get_ray_angle(int number, t_ray sight)
{
	float ray_angle;

	ray_angle = sight.sight_angle + (0.5 - (number/ sight.total_ray)) * sight.horizontal_angle;
	return (ray_angle);
}

int get_cell(int x, int y, t_info *info)
{
	if (x < 0 || x >= info->map_width)
		return (-1);
	if (y < 0 || y >= info->map_height)
		return (-1);
	return (info->map[x][y]);
}

double get_distance(double x0, double y0, double x1, double y1)
{
	double pow;
	
	pow = ((x0 - x1) * (x0 - x1)) + ((y0 - y1) * (y0 - y1));
	return (sqrt(pow));
}

double get_near_point(double now, double move)
{
	double near;

	if (move > 0)
		near = floor(now + 1);
	else if (move < 0)
		near = ceil(now - 1);
	else
		near = now;
	return (near);
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

int is_zero(double d)
{
	if (fabs(d) < 1e-06)
		return (0);
	else if (d > 0)
		return (1);
	else
		return (-1);
}

double get_wall_hit_point(double ray_angle, t_point *now, t_info *info, t_wall *hit)
{
	t_point move;
	t_point slope;
	t_point dist;
	t_point near;
	t_point map;
	int cell;
	double dist_vertical;
	double dist_horizontal;
	double fx;
	double gy;
	
	move.x = is_zero(cos(ray_angle)); //0 초과 ~ 1 :오른쪽, 0 미만 ~ -1: 왼쪽, 0: 움직임 없음
	move.y = is_zero(sin(ray_angle)); // 0 초과 ~ 1: 상단, 0 미만 ~ -1 : 하단, 0 : 움직임 없음
	if (move.x == 0)
		slope.dx = INFINITY;
	else
		slope.dx = tan(ray_angle);
	if (move.y == 0)
		slope.dy = INFINITY;
	else
		slope.dy = 1 / tan(ray_angle);
	near.dx = get_near_point(now->dx, move.x);
	near.dy = get_near_point(now->dy, move.y);
	fx = INFINITY;
	gy = INFINITY;
	
	while(1)
	{
		if (move.x != 0)
			fx = slope.dx * (near.dx - now->dx) + now->dy;
		if (move.y != 0)
			gy = slope.dy * (near.dy - now->dy) + now->dx;
		dist_vertical = get_distance(now->dx, now->dy, near.dx, fx);
		dist_horizontal = get_distance(now->dx, now->dy, gy, near.dy);
		if (dist_vertical < dist_horizontal)
		{
			hit->side = VERTICAL;
			// 세로선과 맞닿는 교점이 더 가까움
			// -> x값을 구하고, f(x)값을 구하기
			if (move.x > 0)
				map.x = (int)near.dx;
			else
				map.x = (int)near.dx - 1;
			map.y = (int)fx;
			if (move.x > 0)
				near.dx += 1;
			else if (move.x < 0)
				near.dx -= 1;
		}
		else
		{
			hit->side = HORIZONTAL;
			// 가로선과 맞닿는 교점이 더 가깝거나, 거리가 같음.
			// -> y값을 구하고, g(y)값을 구하기
			if (move.y > 0)
				map.y = (int)near.dy;
			else
				map.y = (int)near.dy - 1;
			map.x = (int)gy;
			if (move.y > 0)
				near.dy += 1;
			else if (move.y < 0)
				near.dy -= 1;
		}
		// 기울기를 보고, 가져와야하는 맵의 요소를 알기
		// 해당 맵의 요소를 가져와서 벽인지 체크하기
		// 벽이면 return 아니면 continue
		cell = get_cell(map.x, map.y, info);
		if (cell < 0)
			break; // map 밖으로 나감
		if (cell == 1)
		{
			if (hit->side == VERTICAL)
			{
				if (move.x > 0)
					hit->side = DIR_W;
				else
					hit->side = DIR_E;
				hit->wx = near.dx;
				hit->wy = fx;
			}
			else
			{
				if (move.y > 0)
					hit->side = DIR_S;
				else
					hit->side = DIR_N;
				hit->wx = gy;
				hit->wy = near.dy;
			}
			// wx, wy, hit
			//여기서 리턴할것 (벽의 위치, 벽과 맞닿은 방향 (벽이 바라보는 방향))
			return ;
		}
		if (hit->side == VERTICAL)
			near.dx += move.x;
		else
			near.dy += move.y;
		continue;
	}
}

void do_mlx(t_info *info)
{
    t_mlx	mlx;
	t_ray	sight;
	t_point *now;
	t_wall *hit;
	//각 60도에 화면 해상도 720x480 이면, 수직시야각은 다음과 같다고 두는 거.

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WINDOWW, WINDOWH, "cub3D");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WINDOWW, WINDOWH);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bits_per_pixel, \
										&mlx.img.line_length, &mlx.img.endian);
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 5, close_window, &mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
	init_sight(&sight);
	info->map_height = 100;
	info->map_width = 100;
	//px, py : 현재 위치 -> 맵들어오는 거에 따라서, 이동하는 거에 따라서 바꿔줘야함
	now->dx = info->player_x;
	now->dy = info->player_y;
	for (int i = 0; i < sight.total_ray; i++)
	{
		double ray = get_ray_angle(i, sight);
		get_wall_hit_point(ray, now, info, hit);
		double wall_distance = get_distance(now->dx, now->dy, hit->wx, hit->wy);
		printf("Wall Distance : %f", wall_distance);
		double wall_height = get_wall_height(wall_distance, &sight);
		printf("Wall Height : %f", wall_height);
	}
	mlx_loop(mlx.mlx_ptr);
}
