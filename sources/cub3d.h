#ifndef CUB3D_H
#define CUB3D_H

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

typedef struct s_info{
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
} t_info;

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
}	t_mlx;

typedef struct s_ray
{
	float horizontal_angle;
	float vertical_angle;
	float sight_angle;
	int total_ray;
}	t_ray;

//parse_util.c
t_info  *init_info(void);
void    error_in_parsing(char *line, char *str, int fd, t_info *info);
void	print_error_free_info(char *str, t_info *info);
void    free_split(char **split);
int 	create_color(char **split);

//ft_util.c
int     ft_strlen(const char *s);
void    *ft_calloc(size_t count, size_t size);
int     ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);

//raycasting.c
void    do_mlx(t_info *info);

//hook.c
int     key_hook(int keycode, t_mlx *mlx);
int     close_window(t_mlx *mlx);

//parse.c
int 	check_file(int argc, char **argv, t_info *info);
int		parsing(int fd, t_info *info);
int 	check_line_type(char *line);
int 	check_map_line(char *line);
int 	assign_info(int type, char *line, int fd, t_info *info);
int 	check_player(t_info *info);
int		check_map(t_info *info);
int 	check_edge(char *line);
int 	check_first_line(t_info *info);
int 	check_last_line(t_info *info);
int 	check_middle_line(t_info *info);
int 	check_arround_space(char **map, int i, int j, char player);
int 	check_arround_zero(char **map, int i, int j);

//ft_split.c
char	**ft_split(char const *s, char c);

#endif