#include "../headers/cub3d.h"

void	invalid_map(void)
{
	write(1, "map error\n", 11);
	exit(0); //TODO replace exit (make the func return an integer and if the check fails, stop the program by returning 0 in main)
}

void	invalid_texture(void)
{
	write(1, "texture error\n", 15);
	exit(0); //TODO replace exit (make the func return an integer and if the check fails, stop the program by returning 0 in main)
}

error_type texture_check(char *t_path)
{
    if(open(t_path, O_RDONLY) < 0)
        return (TEXTURE_ERROR);
    else
        return (1);
}

error_type color_check(char *t_path)
{
    if(open(t_path, O_RDONLY) < 0)
        return is_color_valid(t_path);
    else
        return (CHECK_OK);
}
