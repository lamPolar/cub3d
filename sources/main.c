/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heeskim <heeskim@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 03:16:07 by heeskim           #+#    #+#             */
/*   Updated: 2022/12/08 03:16:09 by heeskim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_info	*info;

	info = init_info();
	parsing(check_file(argc, argv, info), info);
	init_sight(info->player_char, &info->ray);
	do_mlx(info);
	return (0);
}
