#include "cub3d.h"
extern int g_debug;

void print_altered_map(int x, int y, char c, char **map, int dimX, int dimY)
{
	int i = 0;
	int j = 0;
	while(i < dimY)
	{
		j = 0;
		while(j < dimX)
		{
			if(j == x && y == i)
				printf("%c", c);
			else
				printf("%c", map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void move(t_game *game)
{
	char		**map;
	t_player	*player;
	int			tempX;
	int			tempY;

	player = game->player;
	map = game->map;
	tempX = game->player->posX + game->camera->dirX * SPEED;
	tempY = game->player->posY + game->camera->dirY * SPEED;
	print_altered_map(tempX, tempY, 'X', game->map, game->config->mapMaxWidth, game->config->mapMaxHeight);
	if (map[tempY][tempX] != '1')
	{
		map[((int)player->posY)][((int)player->posX)] = '0';
		map[tempY][tempX] = 'N';
		game->player->posY = tempY;
		game->player->posX = tempX;
		g_debug = 1;
	}
	//ft_print_map(game->map);
}

int	key_hook(int keycode, t_game *game)
{
    (void) game;
    double	x;
    double	y;

	x = 0;
	y = 0;
	if(keycode == D_KEY)
	{
		double oldDirX = game->camera->dirX;
      	game->camera->dirX = oldDirX * cos(-ROT_SPEED) - game->camera->dirY * sin(-ROT_SPEED);
      	game->camera->dirY = oldDirX * sin(-ROT_SPEED) + game->camera->dirY * cos(-ROT_SPEED);
      	double oldPlaneX = game->camera->planeX;
      	game->camera->planeX = game->camera->planeX * cos(-ROT_SPEED) - game->camera->planeY * sin(-ROT_SPEED);
      	game->camera->planeY = oldPlaneX * sin(-ROT_SPEED) + game->camera->planeY * cos(-ROT_SPEED);
	}
	if(keycode == A_KEY)
	{
		double oldDirX = game->camera->dirX;
      	game->camera->dirX = oldDirX * cos(ROT_SPEED) - game->camera->dirY * sin(ROT_SPEED);
      	game->camera->dirY = oldDirX * sin(ROT_SPEED) + game->camera->dirY * cos(ROT_SPEED);
      	double oldPlaneX = game->camera->planeX;
      	game->camera->planeX = game->camera->planeX * cos(ROT_SPEED) - game->camera->planeY * sin(ROT_SPEED);
      	game->camera->planeY = oldPlaneX * sin(ROT_SPEED) + game->camera->planeY * cos(ROT_SPEED);
		// printf("new dirx : %f\n", game->camera->dirX);
		// printf("new diry : %f\n", game->camera->dirY);
	}
	if (keycode == W_KEY)
		move(game);
	if (keycode == S_KEY)
		move(game);
	//vars->cntmoves += move(keycode, vars);
	return (0);
}
