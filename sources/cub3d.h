#ifndef CUB3D_H
#define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include "../mlx/mlx.h"

# define WINDOWW		1000.0
# define WINDOWH		1000.0
# define KEY_W          13
# define KEY_A          0
# define KEY_S          1
# define KEY_D          2
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_ESC		53

typedef struct s_element{
    //해상도 x, y
    //N, W, S, E 벽 텍스쳐
    //sprite 텍스쳐
    //F 색깔
    //C 색깔
    //map x, y ?? 넣을까 말까?
    //map
} t_element;

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

//main.c
void	print_error(char *str);

//util.c
int     ft_strlen(const char *s);
void    *ft_calloc(size_t count, size_t size);
int     ft_atoi(const char *str);

//raycasting.c
void    do_mlx(void);

//hook.c
int     key_hook(int keycode, t_mlx *mlx);
int     close_window(t_mlx *mlx);

#endif