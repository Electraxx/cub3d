#include "cub3d.h"

void	move(t_game *g, int dir)
{
	char		**map;
	t_point		delta;
	t_player	*player;

	map = g->map;
	delta.x = g->camera.dirX * SPEED * dir;
	delta.y = g->camera.dirY * SPEED * dir;
	player = &g->player;
	if (map[(int)(player->pos.y + delta.y)]
	[(int)(player->pos.x + delta.x)] != '1')
	{
		player->pos.x += delta.x;
		player->pos.y += delta.y;
	}
	else if (map[(int)(player->pos.y + delta.y)][(int)(player->pos.x)] == '1'
	&& map[(int)(player->pos.y)][(int)(player->pos.x + delta.x)] != '1')
		player->pos.x += delta.x;
	else if (map[(int)(player->pos.y)][(int)(player->pos.x + delta.x)] == '1'
	&& map[(int)(player->pos.y + delta.y)][(int)(player->pos.x)] != '1')
		g->player.pos.y += delta.y;
	if ((int)(player->pos.y - delta.y) != (int)(player->pos.y)
		|| (int)(player->pos.y - delta.x) != (int)(player->pos.x))
		map[((int)(player->pos.y - delta.y))]
		[((int)(player->pos.x - delta.x))] = '0';
	map[(int)(player->pos.y)][(int)(player->pos.x)] = 'N';
}

void	do_action(t_game *game)
{
	if (game->player.current_action[FRONT_INDEX])
		move(game, 1);
	if (game->player.current_action[BACK_INDEX])
		move(game, -1);
	if (game->player.current_action[R_LEFT_INDEX])
		turncamera(game, 1);
	if (game->player.current_action[R_RIGHT_INDEX])
		turncamera(game, -1);
}

void	turncamera(t_game *game, int dir)
{
	double	odx;
	double	opx;

	opx = game->camera.planeX;
	odx = game->camera.dirX;
	game->camera.dirX = odx * cos(ROT_SPEED * dir)
		- game->camera.dirY * sin(ROT_SPEED * dir);
	game->camera.dirY = odx * sin(ROT_SPEED * dir)
		+ game->camera.dirY * cos(ROT_SPEED * dir);
	game->camera.planeX = game->camera.planeX * cos(ROT_SPEED * dir)
		- game->camera.planeY * sin(ROT_SPEED * dir);
	game->camera.planeY = opx * sin(ROT_SPEED * dir)
		+ game->camera.planeY * cos(ROT_SPEED * dir);
}

int	key_relase(int kc, t_game *game)
{
	if (kc == D_KEY)
		game->player.current_action[R_RIGHT_INDEX] = 0;
	if (kc == A_KEY)
		game->player.current_action[R_LEFT_INDEX] = 0;
	if (kc == W_KEY)
		game->player.current_action[FRONT_INDEX] = 0;
	if (kc == S_KEY)
		game->player.current_action[BACK_INDEX] = 0;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == D_KEY)
		game->player.current_action[R_RIGHT_INDEX] = 1;
	if (keycode == A_KEY)
		game->player.current_action[R_LEFT_INDEX] = 1;
	if (keycode == W_KEY)
		game->player.current_action[FRONT_INDEX] = 1;
	if (keycode == S_KEY)
		game->player.current_action[BACK_INDEX] = 1;
	if (keycode == 14)
		game->player.health += 10;
	return (0);
}
