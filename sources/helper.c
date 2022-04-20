#include "../headers/cub3d.h"

int exit_game(int kc, t_game *game)
{
	free(game->player.current_action);
	exit(0);
}

unsigned int createRGBA(int r, int g, int b, int a)
{
	return ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int	max_height(char **map)
{
	return ft_2dim_char_sz(map);
}

int	max_width(char **map)
{
	size_t	max;
	size_t	i;

	max = 0;
	i = 0;
	while(map[i])
	{
		if(ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return max;
}
