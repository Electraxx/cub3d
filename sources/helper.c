#include "../headers/cub3d.h"

int	exit_game(int kc, t_game *game)
{
	free(game->player.current_action);
	exit(0);
}

unsigned int	creatergba(int r, int g, int b, int a)
{
	size_t	v;

	v = ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
	return (v);
}

int	max_height(char **map)
{
	return (ft_2dim_char_sz(map));
}

int	max_width(char **map)
{
	size_t	max;
	size_t	i;

	max = 0;
	i = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

void	init_buffer(t_image *buf, void *mlxp, int width, int height)
{
	buf->img = mlx_new_image(mlxp, width, height);
	buf->addr = mlx_get_data_addr(buf->img, &buf->bpp, &buf->ll, &buf->endian);
}
