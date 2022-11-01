#ifndef CUB3D_H
#define CUB3D_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

typedef struct s_element{
    //해상도 x, y
    //N, W, S, E 벽 텍스쳐
    //F 색깔
    //C 색깔
    //map x, y ?? 넣을까 말까?
    //map
}

//main.c
void print_error(char *str);

//util.c
int     ft_strlen(const char *s);
void    *ft_calloc(size_t count, size_t size);
int     ft_atoi(const char *str);

//raycasting.c
void    do_mlx(void);

#endif