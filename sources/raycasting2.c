#include "cub3d.h"

void	init_sight(char direction, t_ray **sight)
{
	float angle;
	t_ray *s;

	*sight = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	//if (*sight == NULL)
	// null 처리
	s = *sight;	
	s->horizontal_angle = deg2rad(60);
	if (WINDOWH != 0 && WINDOWW != 0 && s->horizontal_angle != 0)
	{
		angle = s->horizontal_angle / WINDOWW * WINDOWH;
		s->vertical_angle = angle;
	}
	s->total_ray = 20;
	//s->sight_angle = deg2rad(1);
	if (direction == 'N')
		s->sight_angle = deg2rad(90);
	else if (direction == 'W')
		s->sight_angle = deg2rad(270);
	else if (direction == 'S')
		s->sight_angle = deg2rad(180);
	else if (direction == 'E')
		s->sight_angle = deg2rad(0);	
	//여기서 sight_angle을 바라보는 방향에 따라 바꿔주기 (N,S,W,E)
}

void	init_points(t_points *points, t_point *now, double ray_angle)
{
	points->move_x = is_zero(cos(ray_angle)); //0 초과 ~ 1 :오른쪽, 0 미만 ~ -1: 왼쪽, 0: 움직임 없음
	points->move_y = is_zero(sin(ray_angle)); // 0 초과 ~ 1: 상단, 0 미만 ~ -1 : 하단, 0 : 움직임 없음
	if (points->move_x == 0)
		points->slope_x = INFINITY;
	else
		points->slope_x = tan(ray_angle);
	if (points->move_y == 0)
		points->slope_y = INFINITY;
	else
		points->slope_y = 1 / tan(ray_angle);
	points->near_x = get_near_point(now->x, points->move_x);
	points->near_y = get_near_point(now->y, points->move_y);
	points->fx = INFINITY;
	points->gy = INFINITY;
}

void	check_hit_point(t_points *points, t_point *now)
{
	if (points->move_x != 0)
		points->fx = points->slope_x * (points->near_x - now->x) + now->y;
	if (points->move_y != 0)
		points->gy = points->slope_y * (points->near_y - now->y) + now->x;
	points->dist_vertical = get_distance(now->x, now->y, points->near_x, points->fx);
	points->dist_horizon = get_distance(now->x, now->y, points->gy, points->near_y);
}

void	calculate_vertical_point(t_points *points, t_wall *hit)
{
	if (points->move_x > 0)
		points->map_x = (int)points->near_x;
	else
		points->map_x = (int)points->near_x - 1;
	points->map_y = (int)points->fx;
	if (points->move_x > 0)
		points->near_x += 1;
	else if (points->move_x < 0)
		points->near_x -= 1;
	if (points->move_x > 0)
		hit->side = DIR_W;
	else
		hit->side = DIR_E;
	hit->wx = points->near_x;
	hit->wy = points->fx;
}

void	calculate_horizontal_point(t_points *points, t_wall *hit)
{
	if (points->move_y > 0)
		points->map_y = (int)points->near_y;
	else
		points->map_y = (int)points->near_y - 1;
	points->map_x = (int)points->gy;
	if (points->move_y > 0)
		points->near_y += 1;
	else if (points->move_y < 0)
		points->near_y -= 1;
	if (points->move_y > 0)
		hit->side = DIR_S;
	else
		hit->side = DIR_N;
	hit->wx = points->gy;
	hit->wy = points->near_y;
}
