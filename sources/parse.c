/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:36:43 by sojoo             #+#    #+#             */
/*   Updated: 2022/11/11 16:55:20 by sojoo            ###   ########.fr       */
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

    (void)info;
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
            {
                free(line);
                print_error_free_info("Invalid map\n", info);
                exit(1);
            }
            if (assign_info(type, line, info) == 0)
                printf("bomb!\n");
        }
        free(line);
        line = get_next_line(fd);
    }
    //다 저장하고 map 유효 확인 (겉으로 둘러싼거, 캐릭터 위치 등등...)
    // int i = 0;
    // while (i < 4)
    // {
    //     if (info->tex[i] != NULL)
    //         printf("%s\n", info->tex[i]);
    //     i++;
    // }
    close(fd);
    return (1);
}
/*맵 사이에는 빈줄이 들어갈 수 없음*/

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
    // if (*line == '\n')
    //     return (0);
    // 모두 space인 line || nextline만 있는 line 거르기
    while (*line != '\n' && *line != '\0')
    {
        if (*line != '0' && *line != '1' && *line != 'N' && *line != 'S' \
            && *line != 'E' && *line != 'W' && *line != ' ')
            return (0);
        line++;
    }
    return (1);
}

int assign_info(int type, char *line, t_info *info)
{
    int len;
    int i;
    int j;

    if (type >= 0 && type <= 3)
    {
        if (info->tex[type] != NULL)
            return (0);
        i = 2;
        len = 0;
        while (line[i] == ' ')
            i++;
        while (line[i++] != '\n')
            len++;
        info->tex[type] = (char *)calloc(len + 1, sizeof(char));
        if (info == NULL)
            free_info(info);
        i -= len + 1;
        j = 0;
        while (j < len)
            info->tex[type][j++] = line[i++];
        info->tex[type][j] = '\0';
    }
    //c,f 저장 방법
    //map 저장 방법
    return (1);
}
