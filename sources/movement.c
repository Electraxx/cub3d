#include "cub3d.h"

void move(double movX, double movY, t_game *game)
{
	char		**map;
	t_player	*player;

	player = game->player;
	map = game->map;
	movX = movX * SPEED;
	movY = movY * SPEED;
	if (map[(int)(player->posY + movY)][(int)(player->posX + movX)] != '1')
	{
		printf("before x : %f\n", game->player->posX);
		printf("before y : %f\n", game->player->posY);
		printf("before x (cast) : %d\n",(int) game->player->posX);
		printf("before y (cast) : %d\n", (int) game->player->posY);
		map[((int)player->posY)][((int)player->posX)] = '0';
		map[(int)(player->posY + movY)][(int)(player->posX + movX)] = 'N';
		game->player->posY = player->posY + movY;
		game->player->posX = player->posX + movX;
		printf("after x : %f\n", player->posX);
		printf("after y : %f\n", player->posY);
		printf("after x (cast) : %d\n",(int) game->player->posX);
		printf("after y (cast) : %d\n", (int) game->player->posY);
	}
	printf("%f\n", game->player->posX);
	printf("%f\n", game->player->posY);
	ft_print_map(game->map);
}

int	key_hook(int keycode, t_game *game)
{
    (void) game;
    double	x;
    double	y;

	x = 0;
	y = 0;
	if(keycode == A_KEY)
	{
		game->player->v_angle -= 0.1;
		if(game->player->v_angle < 0)
			game->player->v_angle += 2 * PI;
		game->player->deltaX = cos(game->player->v_angle) * ROT_SPEED;
		game->player->deltaY = sin(game->player->v_angle) * ROT_SPEED;
	}
	if(keycode == D_KEY)
	{
		game->player->v_angle += 0.1;
		if(game->player->v_angle > 2 * PI)
			game->player->v_angle -= 2 * PI;
		game->player->deltaX = cos(game->player->v_angle) * ROT_SPEED;
		game->player->deltaY = sin(game->player->v_angle) * ROT_SPEED;
	}
	if(keycode == W_KEY)
		y--;
	if(keycode == S_KEY)
		y++;
	move(x, y, game);
	//vars->cntmoves += move(keycode, vars);
	return (0);
}