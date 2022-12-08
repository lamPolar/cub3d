/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 03:16:07 by heeskim           #+#    #+#             */
/*   Updated: 2022/12/08 12:01:29 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "define.h"

//util.c
double			deg2rad(double d);
int				get_wall_height(double dist_wall, t_ray *sight);

//ft_util.c
int				ft_strlen(const char *s);
void			*ft_calloc(size_t count, size_t size);
int				ft_atoi(const char *str);
int				ft_strncmp(const char *s1, const char *s2, size_t n);

//ft_str_util.c
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strdup(const char *s1);

//ft_split.c
char			**ft_split(char const *s, char c);

//draw.c
int				is_wall_hit(double ray_angle, t_point *now, \
							t_info *info, t_wall *hit);
void			fill_tex_color(t_info *info, t_wall *hit, int x, \
							double wall_height);
void			draw_wall(t_info *info, t_point *now, t_wall *hit);
void			draw_floor_ceiling(t_info *info);
void			drawing(t_info *info);

//mlx.c
void			do_mlx(t_info *info);
void			init_texture(t_info *info);
void			my_mlx_pixel_put(t_img *img, int x, int y, int color);
unsigned int	my_mlx_get_color(t_img *img, int x, int y);

//raycasting_util.c
double			get_ray_angle(int number, t_ray *sight);
int				get_cell(int x, int y, t_info *info);
double			get_distance(double x0, double y0, double x1, double y1);
double			get_near_point(double now, int move);
int				is_zero(double d);

//raycasting.c
void			init_sight(char direction, t_ray **sight);
void			init_points(t_points *points, t_point *now, double ray_angle);
void			check_hit_point(t_points *points, t_point *now);
void			calculate_vertical_point(t_points *points, t_wall *hit);
void			calculate_horizontal_point(t_points *points, t_wall *hit);

//hook.c
int				key_hook(int keycode, t_info *info);
int				close_window(t_info *info);

//parse.c
int				check_file(int argc, char **argv, t_info *info);
void			parsing(int fd, t_info *info);

//parse_line.c
void			check_gnl(int fd, t_info *info);
int				check_line_type(char *line);
int				check_map_line(char *line);

//parse_assign.c
void			assign_info(int type, char *line, int fd, t_info *info);
void			assign_tex(int type, char *line, int fd, t_info *info);
void			assign_color(int type, char *line, int fd, t_info *info);
int				create_color(char **split);

//parse_check.c
int				check_player(t_info *info);
int				check_map(t_info *info);
int				check_edge(char *line);

//parse_map.c
int				check_first_line(t_info *info);
int				check_last_line(t_info *info);
int				check_middle_line(t_info *info);
int				check_arround_space(char **map, int i, int j, char player);
int				check_arround_zero(char **map, int i, int j);

//parse_util.c
t_info			*init_info(void);
void			error_in_parsing(char *line, char *str, int fd, t_info *info);
void			print_error_free_info(char *str, t_info *info);
void			free_split(char **split);

#endif
