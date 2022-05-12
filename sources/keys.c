/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:04:33 by vvermot-          #+#    #+#             */
/*   Updated: 2022/05/03 16:04:34 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

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
