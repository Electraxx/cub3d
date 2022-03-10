# include "../headers/cub3d.h"

int main(int argc, char **argv)
{
    if (argc != 2)
        return (EXIT_FAILURE);
    ft_check_extension(argv[1]);
    ft_parse_first_6_lines(argv[1]);
    return (0);
}
