#include "../headers/cub3d.h"

void load_tile(char tile, size_t posX, size_t posY, t_game *game)
{
	size_t i;
	size_t j;
	int color;
	t_config *conf;

	i =  0;
	j = 0;
	conf = &game->config;
	if (tile == '1')
		color = 0x00ff0000;
	else if (tile == '0')
		color = 0;
	else
		color = 0x000000ff;
	while (i < 16)
	{
		j = 0;
		while (j < 16)
		{
			my_mlx_pixel_put(&game->coll_buffer, j + (posX * 16), i + (posY * 16), color);
			j++;
		}
		i++;
	}
}

int render_frame2D(void *g)
{
	t_game *game = (t_game *)g;
	int i = 0;
	int j = 0;

	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			load_tile(game->map[i][j], j, i, game);
			j++;
		}
		i++;
	}
	//printf("%f %f\n", game->camera->dirX, game->camera->dirY);
	int z = 20;
	double tposx = game->player.pos.x;
	double tposy = game->player.pos.y;
	while (z)
	{
		tposx += game->camera.dirX;
		tposy += game->camera.dirY;
		my_mlx_pixel_put(&game->coll_buffer, (int)(game->player.pos.x * 15) + tposx, (int)(game->player.pos.y * 15) + tposy, 0x0000ff00);
		z--;
	}
	mlx_put_image_to_window(game->mlxp.mlx_ptr, game->mlxp.win_ptr, &game->coll_buffer.img, 0, 0);
	return (0);
}