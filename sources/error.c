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

error_type color_check(char *t_path)
{
    if(open(t_path, O_RDONLY) < 0)
        return is_color_valid(t_path);
    else
        return (CHECK_OK);
}

void	print_error_exit(error_type error)
{
	if (error == MAP_ERROR)
		printf("Map error\n");
	else if (error == TEXTURE_ERROR)
		printf("Texture error\n");
	else if (error == COLOR_ERROR)
		printf("Color error\n");
	else if (error == MISSING_TEXTURE)
		printf("Missing texture error (verify the path)\n");
	else if (error == MISSING_CARDINAL)
		printf("Missing cardinal error\n");
	else if (error == PLAYER_ERROR)
		printf("There should be ONE player on the map\n");
	else if (error == WALL_ERROR)
		printf("The map should be surrounded by walls\n");
	exit(0);
}