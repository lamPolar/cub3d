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
    return (r << 16 + g << 8 + b);
	//return (r << 16 | g << 8 | b);
}

int check_file(char *file)
{
    int fd;

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        print_error("Failed to open file\n");
        exit(1);
    }
    return (fd);
}

int main(int argc, char *argv[])
{
    int fd;

    if (argc != 2)
    {
        print_error("There is no input file\n");
        exit(1);
    }
    fd = check_file(argv[1]);
    // parsing & 구조체에 데이터 넣기 (구조체 free 함수 필요)
    do_mlx();
    // 데이터 가지고 띄우기 (mlx 초기화 & free필요)
    return (0);
}
