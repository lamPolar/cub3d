/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 03:16:07 by heeskim           #+#    #+#             */
/*   Updated: 2022/12/08 11:48:14 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg2rad(double d)
{
	return (d * M_PI / 180.0);
}

int	get_wall_height(double dist_wall, t_ray *sight)
{
	int		wall_height;
	int		wall_pixel_height;
	double	total_height;

	wall_height = 1;
	total_height = dist_wall * tan(sight->vertical_angle / 2.0);
	wall_pixel_height = WINDOWH * wall_height / (2.0 * total_height);
	return (wall_pixel_height);
}
