#include "cub3d.h"

int render_frame(void *g)
{
	printf("render frame called \n");
	t_game *game = (t_game *) g;
	int i = 0;
	int j = 0;
	int color = 0x00FF0000;
	static int ii = 0;
	static int jj = 0;
	while(i < WINDOW_HEIGHT)
	{
		j = 0;
		while(j < WINDOW_WIDTH)
		{
			my_mlx_pixel_put(game->buffer->img, j, i, color);
			j++;
		}
		color+=1;
		i++;
	}
	sleep(1);
	mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->buffer->img, 0, 0);
	ii++;
	jj++;
	return 0;
}

int main(int argc, char **argv)
{
	t_mlxp	mlxp;
	t_cardi_check cardiCheck;
	t_game game;
	t_image img;
	game.player = malloc(sizeof (t_player));
	game.mlxp = &mlxp;
	game.buffer = &img;
	(void) img;
	(void) argc;
	if (argc != 2)
		return (1);
	init_cardi_struct(&cardiCheck);
	ft_parse_file(argv[1], &cardiCheck, &game);
	ft_print_map(game.map);
	mlxp.mlx_ptr = mlx_init();
	mlxp.win_ptr = mlx_new_window(mlxp.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	img.img = mlx_new_image(&mlxp, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	//draw_map(mlx, game);


	mlx_loop_hook(mlxp.mlx_ptr, (void *)render_frame, &game);
	//mlx_key_hook(mlxp.win_ptr, key_hook, &p);
	//mlx_hook(mlxp.win_ptr, 17, 0, close_game, &p);
	
	mlx_loop(mlxp.mlx_ptr);
	/*while(1)
	{
		printf("hahahahahah\n");
	}
	game_loop(&game, &mlxp, &img);*/
}
