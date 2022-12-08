/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 11:41:18 by sojoo             #+#    #+#             */
/*   Updated: 2022/12/08 13:20:26 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <math.h>
# include "../mlx/mlx.h"
# include "../gnl/get_next_line.h"

# define WINDOWW		1920
# define WINDOWH		1080

# define KEY_W          13
# define KEY_A          0
# define KEY_S          1
# define KEY_D          2
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_ESC		53

# define DIR_N 20
# define DIR_S 21
# define DIR_W 22
# define DIR_E 23

# define VERTICAL 0
# define HORIZONTAL 1

# define TEXTURE_SIZE 32

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_img	tex[4];
}	t_mlx;

typedef struct s_ray
{
	float	horizontal_angle;
	float	vertical_angle;
	float	sight_angle;
}	t_ray;

typedef struct s_info{
	t_mlx	*mlx;
	t_ray	*ray;
	char	**tex;
	int		floor;
	int		ceiling;
	char	*map_temp;
	char	**map;
	int		map_width;
	int		map_height;
	char	player_char;
	double	player_x;
	double	player_y;
}	t_info;

typedef struct s_wall{
	int		side;
	double	wx;
	double	wy;
}	t_wall;

typedef struct s_point{
	double	x;
	double	y;
}	t_point;

typedef struct s_points{
	int		move_x;
	int		move_y;
	double	slope_x;
	double	slope_y;
	double	near_x;
	double	near_y;
	int		map_x;
	int		map_y;
	double	dist_vertical;
	double	dist_horizon;
	double	fx;
	double	gy;
}	t_points;

#endif
