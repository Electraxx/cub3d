#include "cub3d.h"

void load_tile(char tile, size_t posX, size_t posY, t_game *game)
{
	size_t	i;
	size_t	j;
	int 	color;
	t_config *conf;

	i = 0;
	j = 0;
	conf = game->config;
	if(tile == '1')
		color = 0x00ff0000;
	else if(tile == '0')
		color = 0;
	else
		color = 0x000000ff;
	while(i < conf->caseHeight)
	{
		j = 0;
		while(j < conf->caseWidth)
		{
			my_mlx_pixel_put(game->buffer, j + (posX * conf->caseWidth), i + (posY * conf->caseHeight), color);
			j++;
		}
		i++;
	}
}

int render_frame(void *g)
{
	t_game *game = (t_game *) g;
	int i = 0;
	int j = 0;

	while(game->map[i])
	{
		j = 0;
			while(game->map[i][j])
			{
				load_tile(game->map[i][j], j, i, game);
				j++;
			}
		i++;
	}
	// sleep(1);
	mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->buffer->img, 0, 0);
	//ft_print_map(game->map);
	//exit(0)
	return 0;
}

int main(int argc, char **argv)
{
	t_mlxp	mlxp;
	t_cardi_check cardiCheck;
	t_game game;
	t_image img;
	game.player = malloc(sizeof (t_player));
	game.config = malloc(sizeof (t_config));
	game.mlxp = &mlxp;
	game.buffer = &img;
	(void) img;
	(void) argc;
	if (argc != 2)
		return (1);
	init_cardi_struct(&cardiCheck);
	ft_parse_file(argv[1], &cardiCheck, &game);
	fill_map(&game.map);
	ft_print_map(game.map);
	mlxp.mlx_ptr = mlx_init();
	mlxp.win_ptr = mlx_new_window(mlxp.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	img.img = mlx_new_image(&mlxp, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	//draw_map(mlx, game);

	game.config->caseHeight = WINDOW_HEIGHT / max_height(game.map);
	game.config->caseWidth = WINDOW_WIDTH / max_width(game.map);
	player_setpos(game.map, game.player);
	mlx_loop_hook(mlxp.mlx_ptr, (void *)render_frame, &game);

	mlx_key_hook(mlxp.win_ptr, key_hook, &game);
	mlx_loop(mlxp.mlx_ptr);
	/*while(1)
	{
		printf("hahahahahah\n");
	}
	game_loop(&game, &mlxp, &img);*/
}
