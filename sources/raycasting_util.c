#include "cub3d.h"

double	get_ray_angle(int number, t_ray *sight)
{
	double ray;

	ray = sight->sight_angle + sight->horizontal_angle * (0.5 - (number / (WINDOWW - 1.0)));
	return (ray);
}

int	get_cell(int x, int y, t_info *info)
{
	if (x < 0 || x >= info->map_width)
		return (-1);	
	if (y < 0 || y >= info->map_height)
		return (-1);
	return (info->map[y][x]);
}

double	get_distance(double x0, double y0, double x1, double y1)
{
	double pow;
	
	pow = ((x0 - x1) * (x0 - x1)) + ((y0 - y1) * (y0 - y1));
	return (sqrt(pow));
}

double	get_near_point(double now, int move)
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

int	is_zero(double d)
{
	if (fabs(d) < 1e-06)
		return (0);
	else if (d > 0)
		return (1);
	else
		return (-1);
}
