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
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
	char	**map;
	int		map_width;
	int		map_height;
	char	player_char;
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

//util.c
void	print_error(char *str);
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

#endif