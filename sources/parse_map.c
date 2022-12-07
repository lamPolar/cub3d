/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojoo <sojoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 22:33:45 by sojoo             #+#    #+#             */
/*   Updated: 2022/12/07 22:37:15 by sojoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
