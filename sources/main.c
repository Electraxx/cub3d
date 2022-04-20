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
	ft_parse_file(argv[1], &cardi, game);
	fill_map(&game->map);
}

void	load_params(t_game *game)
{
	game->player.health = 150;
	game->camera.dirX = -1;
	game->camera.dirY = 0;
	game->player.current_action = malloc(sizeof(int) * 4);
	game->player.current_action[0] = 0;
	game->player.current_action[1] = 0;
	game->player.current_action[2] = 0;
	game->player.current_action[3] = 0;
	game->camera.planeX = 0;
	game->camera.planeY = 0.66;
	game->config.caseWidth = 16;
	game->config.mapMaxHeight = max_height(game->map);
	game->config.caseHeight = 16;
	game->config.mapMaxWidth = max_width(game->map);
	load_textures(game);
	player_setpos(game->map, &game->player);
	get_player_orientation(game->map, &game->config);
	set_player_dir(&game->camera, game->config.firstDir);
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
	game.minimap = malloc(sizeof(t_image));
	load_and_check(&game, argv);
	load_buffers_window(&game);
	load_params(&game);
// TODO Comprendre pourquoi le mouse_hook fait segfault je devienne fou
	loop_init(&game);
//	mlx_mouse_hook(mlxp.win_ptr, get_hp, &game);
//	mlx_key_hook(mlxp.win_ptr, get_hp, &game);
}
