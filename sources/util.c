#include "cub3d.h"

void print_error(char *str)
{
    int len;
    
    len = ft_strlen(str);
    write(1, "Error\n", 6);
    write(1, str, len);
}

int create_color(int r, int g, int b)
{
    return ((r << 16) + (g << 8) + b);
}