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
	conf = game->config;
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
			my_mlx_pixel_put(game->buffer, j + (posX * 16), i + (posY * 16), color);
			j++;
		}
		i++;
	}
}

void fix_png(t_image *img)
{
    int i;
    int j;

    i = 0;
    while(i < 64)
    {
        j = 0;
        while(j < 64)
        {
            if(get_pixel_color(i, j, img->addr) == 4278190080)
                set_pixel_color(i, j, img->addr, 0x00ffffff);
            j++;
        }
        i++;
    }
}

void load_asset(t_image *asset, char *path, t_mlxp *mlxp)
{
	int a;
	int b;

	asset->img = mlx_xpm_file_to_image(mlxp->mlx_ptr, path, &a, &b);
	asset->addr =  mlx_get_data_addr(asset->img, &asset->bits_per_pixel, &asset->line_length, &asset->endian);
	fix_png(asset);
}

void	load_textures(t_game *game)
{
	game->textures->S_texture = malloc(sizeof (t_image));
	game->textures->E_texture = malloc(sizeof (t_image));
	game->textures->W_texture = malloc(sizeof (t_image));
	game->textures->N_texture = malloc(sizeof (t_image));
	load_asset(game->textures->E_texture, "textures/flag.xpm", game->mlxp);
	load_asset(game->textures->S_texture, "textures/wall.xpm", game->mlxp);
	load_asset(game->textures->N_texture, "textures/roz.xpm", game->mlxp);
	load_asset(game->textures->W_texture, "textures/mac64.xpm", game->mlxp);

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
	double tposx = game->player->pos.x;
	double tposy = game->player->pos.y;
	while (z)
	{
		tposx += game->camera->dirX;
		tposy += game->camera->dirY;
		my_mlx_pixel_put(game->buffer, (int)(game->player->pos.x * 15) + tposx, (int)(game->player->pos.y * 15) + tposy, 0x0000ff00);
		z--;
	}
	mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->buffer->img, 0, 0);
	return (0);
}

unsigned int createRGBA(int r, int g, int b, int a)
{
	return ((a & 0xff) << 24) + ((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff);
}

void ft_draw_lifebar(t_game *game)
{
    int		j;
    int		i;

    i = 0;
    while (i < WINDOW_WIDTH / 3)
    {
        j = -1;
        while (++j < 30)
        {
            if (j < 5 || j > 25 || i < 5 || i > WINDOW_WIDTH / 3 - 5)
                my_mlx_pixel_put(game->lifebar, i, j, 0x00ffffff);
            else if (i < game->player->health)
                my_mlx_pixel_put(game->lifebar, i, j, 0x00ff0000);
            else
                my_mlx_pixel_put(game->lifebar, i, j, 0x00000000);
        }
        i++;
    }
    mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->lifebar->img, 10, WINDOW_HEIGHT - 100);
}

char	get_adjacent_cardinal(int vec, char curr)
{
	char	*cardinal;
	int 	i;
	char 	ret;

	i = 0;
	cardinal = ft_strcpy("NESW");
	while(curr != cardinal[i])
			i++;
	i += vec;
	ret = cardinal[i % 4];
	free(cardinal);
	return ret;
}

int key_relase(int kc, t_game *game)
{
	if (kc == D_KEY)
		game->player->current_action[R_RIGHT_INDEX] = 0;
	if (kc == A_KEY)
		game->player->current_action[R_LEFT_INDEX] = 0;
	if (kc == W_KEY)
		game->player->current_action[FRONT_INDEX] = 0;
	if (kc == S_KEY)
		game->player->current_action[BACK_INDEX] = 0;
    return (0);
}

int get_hp(int kc, t_game *game)
{
//	if (kc == 1)
//	{
//		game->player->health += 10;
//		ft_draw_lifebar(game);
//	}
	printf("%d\n", kc);
	return (0);
}

int exit_game(int kc, t_game *game)
{
	exit(0);
}

void set_player_dir(t_camera *camera, char c)
{
	double oldDirX;
	double oldPlaneX;

	oldPlaneX = camera->planeX;
	oldDirX = camera->dirX;

	double deg = 270;
	deg = deg * (PI/180);
	camera->dirX = oldDirX * cos(deg) - camera->dirY * sin(deg);
	camera->dirY = oldDirX * sin(deg) + camera->dirY * cos(deg);
	camera->planeX = camera->planeX * cos(deg) - camera->planeY * sin(deg);
	camera->planeY = oldPlaneX * sin(deg) + camera->planeY * cos(deg);
}

int main(int argc, char **argv)
{
	t_mlxp mlxp;
	t_cardi_check cardiCheck;
	t_game game;
    t_image img;
    t_image lifebar_img;
	game.player = malloc(sizeof(t_player));
	game.config = malloc(sizeof(t_config));
	game.camera = malloc(sizeof(t_camera));
	game.rayIgm = malloc(sizeof(t_image));
	game.textures = malloc(sizeof(t_assets));
	game.texture = malloc(sizeof(t_image));
	game.minimap = malloc(sizeof(t_image));
	game.mlxp = &mlxp;
	game.buffer = &img;
    game.lifebar = &lifebar_img;
	if (argc != 2)
		return (1);
	init_cardi_struct(&cardiCheck);
	ft_parse_file(argv[1], &cardiCheck, &game);
	fill_map(&game.map);
	ft_print_map(game.map);
	mlxp.mlx_ptr = mlx_init();
	mlxp.win_ptr = mlx_new_window(mlxp.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	// game.minimap= mlx_new_image(&mlxp, 400, WINDOW_HEIGHT);
	img.img = mlx_new_image(&mlxp, 1, WINDOW_HEIGHT);
    lifebar_img.img = mlx_new_image(&mlxp, WINDOW_WIDTH / 3, 30);
	// img.img = mlx_new_image(&mlxp, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
    lifebar_img.addr = mlx_get_data_addr(lifebar_img.img, &lifebar_img.bits_per_pixel, &lifebar_img.line_length,
                                         &lifebar_img.endian);
	// game.rayIgm = mlx_new_image(&mlxp, 3, 3);
	// game.rayIgm->addr = mlx_get_data_addr(&game.rayIgm->img, &game.rayIgm->bits_per_pixel, &game.rayIgm->line_length,
	//  &game.rayIgm->endian);
	// draw_map(mlx, game);
    game.player->health = 150;
	game.camera->dirX = -1;
	game.camera->dirY = 0;
	game.player->current_action = malloc(sizeof(int) * 4);
	game.player->current_action[0] = 0;
	game.player->current_action[1] = 0;
	game.player->current_action[2] = 0;
	game.player->current_action[3] = 0;
	game.camera->planeX = 0;
	game.camera->planeY = 0.66;
	game.config->caseWidth = 16;
	game.config->mapMaxHeight = max_height(game.map);
	game.config->caseHeight = 16;
	game.config->mapMaxWidth = max_width(game.map);
	game.config->firstDir = 'W';
	set_player_dir(game.camera, game.config->firstDir);
	load_textures(&game);
	player_setpos(game.map, game.player);
// TODO Comprendre pourquoi le mouse_hook fait segfault je devienne fou
//	mlx_mouse_hook(mlxp.win_ptr, get_hp, &game);
//	mlx_key_hook(mlxp.win_ptr, get_hp, &game);
	mlx_hook(mlxp.win_ptr, 2, 0, key_hook, &game);
	mlx_hook(mlxp.win_ptr, 3, 0, key_relase, &game);
	mlx_hook(mlxp.win_ptr, 17, 0, exit_game, &game);
	mlx_loop_hook(mlxp.mlx_ptr, (void *) draw, &game);
	// mlx_hook(e.win, 2, (1L << 0), &key_press, &e);
	// mlx_loop_hook(mlxp.mlx_ptr, (void *)render_frame2D, &game);
	// printf("%f %f\n", game.player->posX, game.player->posY);
	mlx_loop(mlxp.mlx_ptr);
}
