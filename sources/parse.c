/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:36:43 by sojoo             #+#    #+#             */
/*   Updated: 2022/12/07 20:19:43 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_file(int argc, char **argv, t_info *info)
{
    int fd;

    if (argc != 2)
        print_error_free_info("Please put only one file\n", info);
    if (ft_strncmp(".cub", argv[1] + (ft_strlen(argv[1]) - 4), 4) != 0)
        print_error_free_info("Input file is not .cub file\n", info);
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
        print_error_free_info("Failed to open file\n", info);
    return (fd);
}

int parsing(int fd, t_info *info)
{
    char    *line;
    int     type;
    int     start_map;

    start_map = 0;
    line = get_next_line(fd);
    while (line)
    {
        if (!(*line == '\n' && start_map == 0))
        {
            type = check_line_type(line);
            if (type == 6)
            {
                start_map = 1;
                info->map_height += 1;
            }
            else if (type == -1)
                error_in_parsing(line, "Invalid map\n", fd, info);
            if (assign_info(type, line, fd, info) == 0)
                error_in_parsing(line, "Invalid map\n", fd, info);
        }
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    //다 저장하고 map 유효 확인 (겉으로 둘러싼거, 캐릭터 위치)
    info->map = ft_split(info->map_temp, '\n');
    free(info->map_temp);
    while (info->map[info->map_height - 1][0] == '\0')
        info->map_height--;
    //밑에 빈줄 삭제
    if (check_player(info) == 0 || check_map(info) == 0)
        print_error_free_info("Invalid map\n", info);
    else {
        int i = 0;
        while (i < 4)
        {
            if (info->tex[i] != NULL)
                printf("%s\n", info->tex[i]);
            i++;
        }
        printf("%d\n", info->floor);
        printf("%d\n", info->ceiling);
        i = 0;
        while (info->map[i])
        {
            printf("%s\n", info->map[i]);
            i++;
        }
        printf("%d\n", info->map_width);
        printf("%d\n", info->map_height);
        printf("%c %f %f\n", info->player_char, info->player_x, info->player_y);
    }
    return (1);
}

int check_line_type(char *line)
{
    if (line[0] == 'N' && line[1] == 'O')
        return (0);
    else if (line[0] == 'S' && line[1] == 'O')
        return (1);
    else if (line[0] == 'W' && line[1] == 'E')
        return (2);
    else if (line[0] == 'E' && line[1] == 'A')
        return (3);
    else if (line[0] == 'F' && line[1] == ' ')
        return (4);
    else if (line[0] == 'C' && line[1] == ' ')
        return (5);
    else if (check_map_line(line))
        return (6);
    else
        return (-1);
}

int check_map_line(char *line)
{
    while (*line != '\n' && *line != '\0') //0, 1, 빈칸, 방향 아닌 글자 있으면 탈락
    {
        if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S' \
            && *line != 'E' && *line != 'W' && *line != ' ')
            return (0);
        line++;
    }
    return (1);
}

int assign_info(int type, char *line, int fd, t_info *info)
{
    int len;
    int i;
    int j;
    char    *str;
    char    **split;

    if (type >= 0 && type <= 3) //방향별 텍스처 저장하는 부분
    {
        if (info->tex[type] != NULL) //이미 그 방향이 저장되어 있으면 잘못된 라인
            return (0);
        i = 2;
        len = 0;
        while (line[i] == ' ')
            i++;
        while (line[i++] != '\n')
            len++;
        info->tex[type] = (char *)calloc(len + 1, sizeof(char));
        if (info->tex[type] == NULL)
            error_in_parsing(line, "Failed to allocate memory\n", fd, info);
        i -= len + 1;
        j = 0;
        while (j < len)
            info->tex[type][j++] = line[i++];
        info->tex[type][j] = '\0';
    }
    else if (type == 4)
    {
        if (info->floor != -1)
            return (0);
        i = 1;
        len = 0;
        while (line[i] == ' ')
            i++;
        while (line[i++] != '\n')
            len++;
        str = ft_substr(line, i - len - 1, len);
        split = ft_split(str, ',');
        free(str);
        info->floor = create_color(split);
        if (info->floor == -1)
            return (0);
    }
    else if (type == 5)
    {
        if (info->ceiling != -1)
            return (0);
        i = 1;
        len = 0;
        while (line[i] == ' ')
            i++;
        while (line[i++] != '\n')
            len++;
        str = ft_substr(line, i - len - 1, len);
        split = ft_split(str, ',');
        free(str);
        info->ceiling = create_color(split);
        if (info->ceiling == -1)
            return (0);
    }
    else {
        i = ft_strlen(line);
        if (info->map_width < i)
            info->map_width = i;
        if (info->map_temp == NULL)
            info->map_temp = ft_strdup(line);
        else
            info->map_temp = ft_strjoin(info->map_temp, line);
    }
    return (1);
}

int check_player(t_info *info)
{
    int i;
    int j;

    i = 0;
    while (info->map[i])
    {
        j = 0;
        while (info->map[i][j])
        {
            if (info->map[i][j] == 'N' || info->map[i][j] == 'S' || \
                info->map[i][j] == 'E' || info->map[i][j] == 'W')
            {
                if (info->player_char != 0)
                    return (0);
                info->player_char = info->map[i][j];
                info->player_x = (double)j + 0.5;
                info->player_y = (double)i + 0.5;
            }
            j++;
        }
        i++;
    }
    return (1);
}

int check_map(t_info *info)
{
    if (check_first_line(info) == 0)
        return (0);
    if (check_middle_line(info) == 0)
        return (0);
    if (check_last_line(info) == 0)
        return (0);
    return (1);
}

int check_edge(char *line)
{
    int i;
    int j;

    i = 0;
    while (line[i] == ' ')
        i++;
    j = ft_strlen(line) - 1;
    while (line[j] == ' ')
        j--;
    if (line[i] != '1' || line[j] != '1')
        return (0);
    return (1);
}

int check_first_line(t_info *info)
{
    int i;

    i = 0;
    while (info->map[0][i])
    {
        if (info->map[0][i] == ' ')
        {
            if (ft_strlen(info->map[1]) > i && info->map[1][i] == '0')
                return (0);
        }
        else if (info->map[0][i] != '1')
            return (0);
        i++;
    }
    if (check_edge(info->map[0]) == 0)
        return (0);
    return (1);
}

int check_last_line(t_info *info)
{
    int i;
    int idx;

    i = 0;
    idx = info->map_height - 1;
    while (info->map[idx][i])
    {
        if (info->map[idx][i] == ' ')
        {
            if (ft_strlen(info->map[idx - 1]) > i && \
                info->map[idx - 1][i] == '0')
                return (0);
        }
        else if (info->map[idx][i] != '1')
            return (0);
        i++;
    }
    if (check_edge(info->map[idx]) == 0)
        return (0);
    return (1);
}

int check_middle_line(t_info *info)
{
    int i;
    int j;

    i = 0;
    while (++i < info->map_height - 1)
    {
        if (check_edge(info->map[i]) == 0)
            return (0);
        j = 0;
        while (info->map[i][j])
        {
            if (info->map[i][j] == ' ' && \
                check_arround_space(info->map, i, j, info->player_char) == 0)
                return (0);
            else if ((info->map[i][j] == '0' || info->map[i][j] == info->player_char) && \
                check_arround_zero(info->map, i, j) == 0)
                return (0);
            j++;
        }
    }
    return (1);
}

int check_arround_space(char **map, int i, int j, char player)
{
    if (ft_strlen(map[i - 1]) > j && (map[i - 1][j] == '0' || map[i - 1][j] == player))
        return (0);
    if (ft_strlen(map[i + 1]) > j && (map[i + 1][j] == '0' || map[i + 1][j] == player))
        return (0);
    if (j != 0 && (map[i][j - 1] == '0' || map[i][j - 1] == player))
        return (0);
    if (j != ft_strlen(map[i]) - 1 && (map[i][j + 1] == '0' || map[i][j + 1] == player))
        return (0);
    return (1);
}

int check_arround_zero(char **map, int i, int j)
{
    if (ft_strlen(map[i - 1]) <= j || map[i - 1][j] == ' ')
        return (0);
    if (ft_strlen(map[i + 1]) <= j || map[i + 1][j] == ' ')
        return (0);
    if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
        return (0);
    return (1);
}
