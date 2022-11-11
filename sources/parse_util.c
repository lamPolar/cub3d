#include "cub3d.h"

t_info  *init_info(void)
{
    t_info  *info;

    info = (t_info *)calloc(1, sizeof(t_info));
    if (info == NULL)
        exit(1);
    info->tex = (char **)calloc(4, sizeof(char *));
    if (info->tex == NULL)
    {
        free(info);
        exit(1);
    }
    info->floor = 0;
    info->ceiling = 0;
    info->map = NULL;
    info->map_width = 0;
    info->map_height = 0;
    info->player_char = 0;
    info->player_x = 0;
    info->player_y = 0;
    return (info);
}

void    print_error_free_info(char *str, t_info *info)
{
    printf("Error\n%s", str);
    free_info(info);
}

void    free_info(t_info *info)
{
    int i;

    i = 0;
    while (i < 4)
    {
        if (info->tex[i] != NULL)
            free(info->tex[i]);
        i++;
    }
    free(info->tex);
    free(info);
    exit(1);
}

int create_color(int r, int g, int b)
{
    return ((r << 16) + (g << 8) + b);
}