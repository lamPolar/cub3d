#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
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
	char	**map;
	int		map_width;
	int		map_height;
	char	player_char;
	int		player_x;
	int		player_y;
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

//parse_util.c
t_info  *init_info(void);
void	print_error_free_info(char *str, t_info *info);
void    free_info(t_info *info);
int 	create_color(int r, int g, int b);

//ft_util.c
int     ft_strlen(const char *s);
void    *ft_calloc(size_t count, size_t size);
int     ft_atoi(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

//raycasting.c
void    do_mlx(void);

//hook.c
int     key_hook(int keycode, t_mlx *mlx);
int     close_window(t_mlx *mlx);

//parse.c
int 	check_file(int argc, char **argv, t_info *info);
int		parsing(int fd, t_info *info);
int 	check_line_type(char *line);
int 	check_map_line(char *line);
int 	assign_info(int type, char *line, t_info *info);

#endif