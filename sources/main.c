#include "cub3d.h"

int check_file(int argc, char **argv, t_info *info)
{
    int fd;

    if (argc != 2)
    {
        print_error("Please put only one file\n");
        free(info);
        exit(1);
    }
    if (ft_strncmp(".cub", argv[1] + (ft_strlen(argv[1]) - 4), 4) != 0)
    {
        print_error("Input file is not .cub file\n");
        free(info);
        exit(1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        print_error("Failed to open file\n");
        free(info);
        exit(1);
    }
    return (fd);
}

int parsing(int fd, t_info *info)
{
    char    *str;

    str = get_next_line(fd);

    close(fd);
    return (1);
}

int main(int argc, char **argv)
{
    t_info   *info;

    info = (t_info *)calloc(1, sizeof(t_info));
    if (info == NULL)
    {
        print_error("Failed to allocate memory\n");
        return (1);
    }
    if (parsing(check_file(argc, argv, info), info) == 0) //안에서 에러메시지 및 info free 하기
        return (1);
    // do_mlx();
    // 데이터 가지고 띄우기 (mlx 초기화 & free필요)
    return (0);
}