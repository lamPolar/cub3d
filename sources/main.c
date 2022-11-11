#include "cub3d.h"

int main(int argc, char **argv)
{
    t_info   *info;

    info = init_info();
    if (parsing(check_file(argc, argv, info), info) == 0) //안에서 에러메시지 및 info free 하기
        return (1);
    // do_mlx();
    // 데이터 가지고 띄우기 (mlx 초기화 & free필요)
    return (0);
}