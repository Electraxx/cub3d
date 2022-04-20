#include "cub3d.h"
int g_debug = 0;

void load_tile(char tile, size_t posX, size_t posY, t_game *game)
{
	size_t i;
	size_t j;
	int color;
	t_config *conf;

	i =  0;
	j = 0;
	conf = &game->config;
	if (tile == '1')
		color = 0x00ff0000;
	else if (tile == '0')
		color = 0;
	else
		color = 0x000000ff;
	while (i < 16)
	{
		j = 0;
		while (j < 16)
		{
			my_mlx_pixel_put(&game->coll_buffer, j + (posX * 16), i + (posY * 16), color);
			j++;
		}
		i++;
	}
}

int render_frame2D(void *g)
{
	t_game *game = (t_game *)g;
	int i = 0;
	int j = 0;

	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			load_tile(game->map[i][j], j, i, game);
			j++;
		}
		i++;
	}
	//printf("%f %f\n", game->camera->dirX, game->camera->dirY);
	int z = 20;
	double tposx = game->player.pos.x;
	double tposy = game->player.pos.y;
	while (z)
	{
		tposx += game->camera.dirX;
		tposy += game->camera.dirY;
		my_mlx_pixel_put(&game->coll_buffer, (int)(game->player.pos.x * 15) + tposx, (int)(game->player.pos.y * 15) + tposy, 0x0000ff00);
		z--;
	}
	mlx_put_image_to_window(game->mlxp.mlx_ptr, game->mlxp.win_ptr, &game->coll_buffer.img, 0, 0);
	return (0);
}

unsigned int createRGBA(int r, int g, int b, int a)
{
	return ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

int key_relase(int kc, t_game *game)
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

int exit_game(int kc, t_game *game)
{
	free(game->player.current_action);
	exit(0);
}

void	init(t_game *game)
{

}

void loop_init(t_game *game)
{
	mlx_hook(game->mlxp.win_ptr, 2, 0, key_hook, game);
	mlx_hook(game->mlxp.win_ptr, 3, 0, key_relase, game);
	mlx_hook(game->mlxp.win_ptr, 17, 0, exit_game, game);
	mlx_loop_hook(game->mlxp.mlx_ptr, (void *) draw, game);
	mlx_loop(game->mlxp.mlx_ptr);
}

void	load_and_check(t_game *game, char **argv)
{
	t_cardi_check cardiCheck;

	init_cardi_struct(&cardiCheck);
	ft_parse_file(argv[1], &cardiCheck, game);
	fill_map(&game->map);
}

void load_params(t_game *game)
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

void	load_buffers(t_game *game)
{
	game->mlxp.mlx_ptr = mlx_init();
	game->mlxp.win_ptr = mlx_new_window(game->mlxp.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	game->coll_buffer.img = mlx_new_image(game->mlxp.mlx_ptr, 1, WINDOW_HEIGHT);
	game->lifebar.img = mlx_new_image(game->mlxp.mlx_ptr, WINDOW_WIDTH / 3, 30);
	game->coll_buffer.addr = mlx_get_data_addr(game->coll_buffer.img, &game->coll_buffer.bits_per_pixel, &game->coll_buffer.line_length,
											  &game->coll_buffer.endian);
	game->lifebar.addr = mlx_get_data_addr(game->lifebar.img, &game->lifebar.bits_per_pixel, &game->lifebar.line_length,
										  &game->lifebar.endian);
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (1);
	game.minimap = malloc(sizeof(t_image));
	load_and_check(&game, argv);
	load_buffers(&game);
	load_params(&game);
// TODO Comprendre pourquoi le mouse_hook fait segfault je devienne fou
	loop_init(&game);
//	mlx_mouse_hook(mlxp.win_ptr, get_hp, &game);
//	mlx_key_hook(mlxp.win_ptr, get_hp, &game);
}
