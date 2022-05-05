/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:04:25 by vvermot-          #+#    #+#             */
/*   Updated: 2022/05/03 16:06:21 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	loop_init(t_game *game)
{
	mlx_hook(game->mlxp.win_ptr, 2, 0, key_hook, game);
	mlx_hook(game->mlxp.win_ptr, 3, 0, key_relase, game);
	mlx_hook(game->mlxp.win_ptr, 17, 0, exit_game, game);
	mlx_loop_hook(game->mlxp.mlx_ptr, (void *) draw, game);
	mlx_loop(game->mlxp.mlx_ptr);
}

void	load_and_check(t_game *game, char **argv)
{
	t_cardi_check	cardi;

	init_cardi_struct(&cardi);
	if(ft_parse_file(argv[1], &cardi, game) != CHECK_OK)
	{
		printf("file error\n");
		exit(0);
	}
	fill_map(&game->map);
}

void	load_params(t_game *game)
{
	game->player.health = 150;
	game->camera.dirx = -1	;
	game->camera.diry = 0;
	game->player.current_action = malloc(sizeof(int) * 4);
	game->player.current_action[0] = 0;
	game->player.current_action[1] = 0;
	game->player.current_action[2] = 0;
	game->player.current_action[3] = 0;
	game->camera.planex = 0;
	game->camera.planey = 0.66;
	load_textures(game);
	player_setpos(game->map, &game->player);
	get_player_orientation(game->map, &game->config);
	set_player_dir(&game->camera, game->config.firstdir);
}

void	load_buffers_window(t_game *game)
{
	game->mlxp.mlx_ptr = mlx_init();
	game->mlxp.win_ptr = mlx_new_window(game->mlxp.mlx_ptr, W_W, W_H, "cub3d");
	init_buffer(&game->coll_buffer, game->mlxp.mlx_ptr, 1, W_H);
	init_buffer(&game->lifebar, game->mlxp.mlx_ptr, W_W / 3, 30);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	load_and_check(&game, argv);
	load_buffers_window(&game);
	load_params(&game);
	loop_init(&game);
}
