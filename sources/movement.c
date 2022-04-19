#include "cub3d.h"

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
	if (map[(int)(game->player->pos.y + deltay)][(int)(game->player->pos.x + deltax)] != '1')
	{
		game->player->pos.x += deltax;
		game->player->pos.y += deltay;
	}
    // The two else if are here to check for wall slides
    // TODO Maybe modifier la speed quand tu wall slide
    // TODO Fix Crash quand on fonce dans les coins | SHOULD BE FINE
    else if (map[(int)(game->player->pos.y + deltay)][(int)(game->player->pos.x)] == '1'
        && map[(int)(game->player->pos.y)][(int)(game->player->pos.x + deltax)] != '1')
        game->player->pos.x += deltax;
    else if (map[(int)(game->player->pos.y)][(int)(game->player->pos.x + deltax)] == '1'
        && map[(int)(game->player->pos.y + deltay)][(int)(game->player->pos.x)] != '1')
        game->player->pos.y += deltay;
    if ((int)(player->pos.y - deltay) != (int)(player->pos.y) || (int)(player->pos.y - deltax) != (int)(player->pos.x))
        map[((int)(player->pos.y - deltay))][((int)(player->pos.x - deltax))] = '0';
    map[(int)(player->pos.y)][(int)(player->pos.x)] = 'N';
}

void do_action(t_game *game)
{
	if(game->player->current_action[FRONT_INDEX])
		move(game, 1);
	if(game->player->current_action[BACK_INDEX])
		move(game, -1);
	if(game->player->current_action[R_LEFT_INDEX])
		turnCamera(game, 1);
	if(game->player->current_action[R_RIGHT_INDEX])
		turnCamera(game, -1);
}

void update_player_direction(t_game *game)
{
	double heading = atan2(game->camera->dirY, game->camera->dirX) * (180 / PI) + 180;
	char c;
	if (heading > 315 || heading < 45)
		c = 'W';
	if (heading > 45 && heading < 135)
		c = 'N';
	if (heading > 135 && heading < 225)
		c = 'E';
	if (heading > 225 && heading < 315)
		c = 'S';
	game->player->dirState = c;
//	printf("heading : %c (%f)\n", c, heading);
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
	update_player_direction(game);
}

int key_hook(int keycode, t_game *game)
{
	if (keycode == D_KEY)
		game->player->current_action[R_RIGHT_INDEX] = 1;
	if (keycode == A_KEY)
		game->player->current_action[R_LEFT_INDEX] = 1;
	if (keycode == W_KEY)
		game->player->current_action[FRONT_INDEX] = 1;
	if (keycode == S_KEY)
		game->player->current_action[BACK_INDEX] = 1;
	if (keycode == 14)
		game->player->health += 10;
//	ft_draw_lifebar(game);
	return (0);
}
