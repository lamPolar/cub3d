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
    info->floor = -1;
    info->ceiling = -1;
    info->map_temp = NULL;
    info->map = NULL;
    info->map_width = 0;
    info->map_height = 0;
    info->player_char = 0;
    info->player_x = 0;
    info->player_y = 0;
    return (info);
}

void    error_in_parsing(char *line, char *str, int fd, t_info *info)
{
    free(line);
    close(fd);
    print_error_free_info(str, info);
}

void    print_error_free_info(char *str, t_info *info)
{
    int i;

    printf("Error\n%s", str);
    i = 0;
    while (i < 4)
    {
        if (info->tex[i] != NULL)
            free(info->tex[i]);
        i++;
    }
    free(info->tex);
    if (info->map_temp)
        free(info->map_temp);
    if (info->map)
        free_split(info->map);
    free(info);
    exit(1);
}

void    free_split(char **split)
{
    int i;

    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}
