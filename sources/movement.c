/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:04:33 by vvermot-          #+#    #+#             */
/*   Updated: 2022/05/03 16:04:34 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_point	get_perpendicular_vector(t_point dir)
{
	t_point	perp;

	perp.x = dir.y * -1;
	perp.y = dir.x;
	return (perp);
}

void	move(t_game *g, int dir, int straffe)
{
	char		**map;
	t_point		delta;
	t_player	*player;
	t_point		straffvec;

	if (straffe)
	{
		straffvec.x = g->camera.dirx;
		straffvec.y = g->camera.diry;
		straffvec = get_perpendicular_vector(straffvec);
		delta.x = straffvec.x * SPEED * dir;
		delta.y = straffvec.y * SPEED * dir;
	}
	else
	{
		delta.x = g->camera.dirx * SPEED * dir;
		delta.y = g->camera.diry * SPEED * dir;
	}
	map = g->map;
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
		move(game, 1, 0);
	if (game->player.current_action[BACK_INDEX])
		move(game, -1, 0);
	if (game->player.current_action[R_LEFT_INDEX])
		turncamera(game, 1);
	if (game->player.current_action[R_RIGHT_INDEX])
		turncamera(game, -1);
	if (game->player.current_action[STRAFE_LEFT_INDEX])
		move(game, 1, 1);
	if (game->player.current_action[STRAFE_RIGHT_INDEX])
		move(game, -1, 1);
}

void	turncamera(t_game *game, int dir)
{
	double	odx;
	double	opx;

	opx = game->camera.planex;
	odx = game->camera.dirx;
	game->camera.dirx = odx * cos(ROT_SPEED * dir)
		- game->camera.diry * sin(ROT_SPEED * dir);
	game->camera.diry = odx * sin(ROT_SPEED * dir)
		+ game->camera.diry * cos(ROT_SPEED * dir);
	game->camera.planex = game->camera.planex * cos(ROT_SPEED * dir)
		- game->camera.planey * sin(ROT_SPEED * dir);
	game->camera.planey = opx * sin(ROT_SPEED * dir)
		+ game->camera.planey * cos(ROT_SPEED * dir);
}

int	key_relase(int kc, t_game *game)
{
	if (kc == D_KEY)
		game->player.current_action[STRAFE_RIGHT_INDEX] = 0;
	if (kc == A_KEY)
		game->player.current_action[STRAFE_LEFT_INDEX] = 0;
	if (kc == W_KEY)
		game->player.current_action[FRONT_INDEX] = 0;
	if (kc == S_KEY)
		game->player.current_action[BACK_INDEX] = 0;
	if (kc == R_ARROW_KEY)
		game->player.current_action[R_RIGHT_INDEX] = 0;
	if (kc == L_ARROW_KEY)
		game->player.current_action[R_LEFT_INDEX] = 0;
	return (0);
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == ESC_KEY)
		exit(0);
	if (keycode == D_KEY)
		game->player.current_action[STRAFE_RIGHT_INDEX] = 1;
	if (keycode == A_KEY)
		game->player.current_action[STRAFE_LEFT_INDEX] = 1;
	if (keycode == L_ARROW_KEY)
		game->player.current_action[R_LEFT_INDEX] = 1;
	if (keycode == R_ARROW_KEY)
		game->player.current_action[R_RIGHT_INDEX] = 1;
	if (keycode == W_KEY)
		game->player.current_action[FRONT_INDEX] = 1;
	if (keycode == S_KEY)
		game->player.current_action[BACK_INDEX] = 1;
	if (keycode == 14)
		game->player.health += 10;
	return (0);
}
