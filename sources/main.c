#include "cub3d.h"

int main(int argc, char **argv)
{
    t_info   *info;

    info = init_info();
    parsing(check_file(argc, argv, info), info); //안에서 에러메시지 및 info free 하기
	init_sight(info->player_char, &info->ray);
    do_mlx(info);// 데이터 가지고 띄우기 (mlx 초기화 & free필요)
    return (0);
}