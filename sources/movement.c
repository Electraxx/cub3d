#include "cub3d.h"
extern int g_debug;

void print_altered_map(int x, int y, char c, char **map, int dimX, int dimY)
{
	int i = 0;
	int j = 0;
	while (i < dimY)
	{
		j = 0;
		while (j < dimX)
		{
			if (j == x && y == i)
				printf("%c", c);
			else
				printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void move(t_game *game, int dir)
{
	char		**map;
	double		deltax;
	double		deltay;
	t_player	*player;

	player = game->player;
	map = game->map;
	deltax = game->camera->dirX * SPEED * dir;
	deltay = game->camera->dirY * SPEED * dir;
	if (map[(int)(game->player->posY + deltay)][(int)(game->player->posX + deltax)] != '1')
	{
		game->player->posX += deltax;
		game->player->posY += deltay;
		if ((int)(player->posY - deltay) != (int)(player->posY) || (int)(player->posY - deltax) != (int)(player->posX))
			map[((int)(player->posY - deltay))][((int)(player->posX - deltax))] = '0';
		map[(int)(player->posY)][(int)(player->posX)] = 'N';
	}
}

void turnCamera(t_game *game, int dir)
{
	double oldDirX;
	double oldPlaneX;
	
	oldPlaneX = game->camera->planeX;
	oldDirX = game->camera->dirX;
	game->camera->dirX = oldDirX * cos(ROT_SPEED * dir) - game->camera->dirY * sin(ROT_SPEED * dir);
	game->camera->dirY = oldDirX * sin(ROT_SPEED * dir) + game->camera->dirY * cos(ROT_SPEED * dir);
	game->camera->planeX = game->camera->planeX * cos(ROT_SPEED * dir) - game->camera->planeY * sin(ROT_SPEED * dir);
	game->camera->planeY = oldPlaneX * sin(ROT_SPEED * dir) + game->camera->planeY * cos(ROT_SPEED * dir);
}

int key_hook(int keycode, t_game *game)
{
	if (keycode == D_KEY)
		turnCamera(game, -1);
	if (keycode == A_KEY)
		turnCamera(game, 1);
	if (keycode == W_KEY)
		move(game, 1);
	if (keycode == S_KEY)
		move(game, -1);
	return (0);
}
