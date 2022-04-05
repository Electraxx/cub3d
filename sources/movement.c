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

double roundnearest125(double nbr)
{
	double testnbr = -1;
	double lowest_delta = 100000;
	int i = 1;
	int itnbr = 0;
	int negcheck = 1;
	if(nbr < 0)
		negcheck -=2;
	while(i < 17)
	{
		double debug = fabs(((i) * 0.100) - fabs(nbr));
		if(lowest_delta > fabs((i * 0.) - fabs(nbr)))
		{
			itnbr = i;
			lowest_delta = fabs(fabs(i * 0.125) - fabs(nbr));
		}
		i++;
	}
	return itnbr * 0.125 * negcheck;
}

void move(double deltax, double deltay, t_game *game)
{
	char		**map;
	t_player	*player;

	player = game->player;
	map = game->map;

	//deltax = roundnearest125(deltax);
	//deltay = roundnearest125(deltay);
	if (fabs(deltax) < 0.06)
		deltax = 0.0;
	if (fabs(deltay) < 0.06)
		deltay = 0.0;
	// int testx = (int)deltax * 100;
	// int testy = (int)deltay * 100;
	// if(testx % 10 >= 5)
	// 	testx += testx % 10;
	// if(testx % 10 >= 5)
	// 	testx += testx % 10;
	// deltay = ceilf(deltay);
	// deltax = ceilf(deltax);
	// printf("altered map : \n");
	// print_altered_map(tempX, tempY, 'X', game->map, game->config->mapMaxWidth, game->config->mapMaxHeight);
	if (map[(int)(game->player->posY + deltay)][(int)(game->player->posX + deltax)] != '1')
	{
		game->player->posX += deltax;
		game->player->posY += deltay;
		printf("PosX: %f\tPosy: %f\ndeltaX: %f\tdeltaY: %f\n", game->player->posX, game->player->posY, deltax, deltay);
		printf("Dirx: %f\tDiry: %f\n", game->camera->dirX, game->camera->dirY);
		if((int)(player->posY - deltay) != (int)(player->posY) || (int)(player->posY - deltax) != (int)(player->posX))
			map[((int)(player->posY - deltay))][((int)(player->posX -deltax))] = '0';
		map[(int)(player->posY)][(int)(player->posX)] = 'N';
		// game->player->posY = tempY;
		// game->player->posX = tempX;
	}
	//printf("real map : \n");
	//ft_print_map(game->map);
}

int	key_hook(int keycode, t_game *game)
{
    (void) game;
    double	x;
    double	y;
	static int count = 0;
	double	tempX;
	double	tempY;

	x = 0;
	y = 0;
	count++;
	if(keycode == D_KEY)
	{
		double oldDirX = game->camera->dirX;
      	game->camera->dirX = oldDirX * cos(-ROT_SPEED) - game->camera->dirY * sin(-ROT_SPEED);
      	game->camera->dirY = oldDirX * sin(-ROT_SPEED) + game->camera->dirY * cos(-ROT_SPEED);
      	double oldPlaneX = game->camera->planeX;
      	game->camera->planeX = game->camera->planeX * cos(-ROT_SPEED) - game->camera->planeY * sin(-ROT_SPEED);
      	game->camera->planeY = oldPlaneX * sin(-ROT_SPEED) + game->camera->planeY * cos(-ROT_SPEED);
		// printf("Dirx: %f\tDiry: %f\n", game->camera->dirX, game->camera->dirY);
	}
	if(keycode == A_KEY)
	{
		double oldDirX = game->camera->dirX;
      	game->camera->dirX = oldDirX * cos(ROT_SPEED) - game->camera->dirY * sin(ROT_SPEED);
      	game->camera->dirY = oldDirX * sin(ROT_SPEED) + game->camera->dirY * cos(ROT_SPEED);
      	double oldPlaneX = game->camera->planeX;
      	game->camera->planeX = game->camera->planeX * cos(ROT_SPEED) - game->camera->planeY * sin(ROT_SPEED);
      	game->camera->planeY = oldPlaneX * sin(ROT_SPEED) + game->camera->planeY * cos(ROT_SPEED);
		// printf("Dirx: %f\tDiry: %f\n", game->camera->dirX, game->camera->dirY);

	}
	if (keycode == W_KEY)
	{
		// tempY = game->player->posY + game->camera->dirY * SPEED;
		// tempX = game->player->posX + game->camera->dirX * SPEED;
	// 	if (fabs(game->camera->dirX) > fabs(game->camera->dirY))
	// 		move(game->camera->dirX * SPEED, 0, game);
	// 	else
	// 		move(0, game->camera->dirY * SPEED, game);
		move(game->camera->dirX * SPEED, game->camera->dirY * SPEED, game);
	}
	if (keycode == S_KEY)
	{
		// if (fabs(game->camera->dirX) > fabs(game->camera->dirY))
		// 	move(game->camera->dirX * SPEED * -1, 0, game);
		// else
		// 	move(0, game->camera->dirY * SPEED * -1, game);
		move(game->camera->dirX * SPEED * -1, game->camera->dirY * SPEED * -1, game);
	}
	return (0);
}
