#include "cub3d.h"

void my_mlx_pixel_put(t_img *data, int x, int y, int color){
	char *dst;

	dst = data->addr + (y * data -> line_length + x *( data->bits_per_pixel / 8));
	//괄호 = offset
	*(unsigned int *) dst = color;
}

void	get_vertical_view_angle(t_ray *sight)
{
	float angle;

	if (WINDOWH != 0 && WINDOWW != 0 && sight->horizontal_angle != 0)
	{
		angle = sight->horizontal_angle / WINDOWW * WINDOWH;
		sight->vertical_angle = angle;
	}
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
	int wall_height = 1;
	double total_height = dist_wall * tan(sight->vertical_angle/2.0);
	int wall_pixel_height = WINDOWH * wall_height / (2.0 * total_height);
	return (wall_pixel_height);
}

double get_wall_hit_point(double ray_angle, double px, double py, t_info *info)
{
	int move_x;
	int move_y;
	double slope_x;
	double slope_y;
	double dist_vertical;
	double dist_horizontal;
	double near_x;
	double near_y;
	double fx;
	double gy;
	
	move_x = cos(ray_angle); //0 초과 ~ 1 :오른쪽, 0 미만 ~ -1: 왼쪽, 0: 움직임 없음
	move_y = sin(ray_angle); // 0 초과 ~ 1: 상단, 0 미만 ~ -1 : 하단, 0 : 움직임 없음
	if (move_x == 0)
		slope_x = INFINITY;
	else
		slope_x = tan(ray_angle);
	if (move_y == 0)
		slope_y = INFINITY;
	else
		slope_y = 1 / tan(ray_angle);

	near_x = get_near_point(px, move_x);
	near_y = get_near_point(py, move_y);
	fx = INFINITY;
	gy = INFINITY;
	
	int next_x;
	int next_y;
	
	while(1)
	{
		if (move_x != 0)
			fx = slope_x * (near_x - px) + py;
		if (move_y != 0)
			gy = slope_y * (near_y - py) + px;
		dist_vertical = get_distance(px, py, near_x, fx);
		dist_horizontal = get_distance(px, py, gy, near_y);

		if (dist_vertical < dist_horizontal)
		{
			// 세로선과 맞닿는 교점이 더 가까움
			// -> x값을 구하고, f(x)값을 구하기
			if (move_x > 0)
				next_x = (int)near_x;
			else
				next_x = (int)near_x - 1;
			next_y = (int)fx;
			if (move_x > 0)
				near_x += 1;
			else if (move_x < 0)
				near_x -= 1;
			// 기울기를 보고, 가져와야하는 맵의 요소를 알기
			// 해당 맵의 요소를 가져와서 벽인지 체크하기
			// 벽이면 return 아니면 continue
		}
		else
		{
			// 가로선과 맞닿는 교점이 더 가깝거나, 거리가 같음.
			// -> y값을 구하고, g(y)값을 구하기
			if (move_y > 0)
				next_y = (int)near_y;
			else
				next_y = (int)near_y - 1;
			next_x = (int)gy;
			if (move_y > 0)
				near_y += 1;
			else if (move_y < 0)
				near_y -= 1;
			// 기울기를 보고, 가져와야하는 맵의 요소를 알기
			// 해당 맵의 요소를 가져와서 벽인지 체크하기
			// 벽이면 return 아니면 continue
		}
		int cell;
		cell = get_cell(next_x, next_y, info);
		if (cell == 1)
		{
			//여기서 리턴할것 (벽의 위치, 벽까지의 거리, vertical or horizontal?)
			//아니면 아예 벽까지의 거리를 계산해서 리턴?
			double dist_wall = get_distance(px, py, next_x, next_y);
			return dist_wall; //여기서 리턴해줘야될게 뭔지 정해야됨
		}
		continue;
	}
}

void do_mlx(t_info *info)
{
    t_mlx	mlx;
	//각 60도에 화면 해상도 720x480 이면, 수직시야각은 다음과 같다고 두는 거.

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, WINDOWW, WINDOWH, "Cub3D");
	mlx.img.img_ptr = mlx_new_image(mlx.mlx_ptr, WINDOWW, WINDOWH);
	mlx.img.addr = mlx_get_data_addr(mlx.img.img_ptr, &mlx.img.bits_per_pixel, \
										&mlx.img.line_length, &mlx.img.endian);
	mlx_key_hook(mlx.win_ptr, key_hook, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 5, close_window, &mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img.img_ptr, 0, 0);
    t_ray sight;
	sight.horizontal_angle = 60;
	get_vertical_view_angle(&sight);
	sight.total_ray = 6;
	sight.sight_angle = 1;
	info->map_height = 100;
	info->map_width = 100;
	double px = 10;
	double py = 10;
	for (int i = 0; i < sight.total_ray; i++)
	{
		double ray = get_ray_angle(i, sight);
		double wall_distance = get_wall_hit_point(ray, px, py, info);
		printf("Wall Distance : %f", wall_distance);
	}
	mlx_loop(mlx.mlx_ptr);
}
