#include "cub3d.h"
int g_debug = 0;

void load_tile(char tile, size_t posX, size_t posY, t_game *game)
{
	size_t i;
	size_t j;
	int color;
	t_config *conf;

	i = 0;
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

void	load_textures(t_game *game)
{
	int a;
	int b;
	game->textures->wallText = mlx_xpm_file_to_image(game->mlxp->mlx_ptr, "textures/mac64.xpm", &a, &b);
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
	printf("%f %f\n", game->camera->dirX, game->camera->dirY);
	double rayx = game->player->posX + game->player->posX * (fabs(game->camera->dirX));
	double rayy = game->player->posY + game->player->posY * (fabs(game->camera->dirY));
	int z = 20;
	double tposx = game->player->posX;
	double tposy = game->player->posY;
	while (z)
	{
		tposx += game->camera->dirX;
		tposy += game->camera->dirY;
		my_mlx_pixel_put(game->buffer, (int)(game->player->posX * 15) + tposx, (int)(game->player->posY * 15) + tposy, 0x0000ff00);
		z--;
	}
	mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->buffer->img, 0, 0);
	return (0);
}

unsigned long createRGBA(t_color color)
{
	return ((color.r & 0xff) << 24) + ((color.g & 0xff) << 16) + ((color.b & 0xff) << 8) + (color.a & 0xff);
}

void ft_verline(int line, int *drawStart_end, t_game *game, int color)
{
	int i;

	i = 0;
	while (i < drawStart_end[0])
	{
		my_mlx_pixel_put(game->buffer, 0, i, 0x00ff0000);
		i++;
	}
	while (i < drawStart_end[1])
	{
		my_mlx_pixel_put(game->buffer, 0, i, color);
		i++;
	}
	while (i < WINDOW_HEIGHT - 200)
	{
		my_mlx_pixel_put(game->buffer, 0, i, 0x0000ff00);
		i++;
	}
	mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->buffer->img, line, 0);
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

void drawRays3D(void *g)
{
	int done = 0;
	int i = 0;
	double sideDistX;
	double sideDistY;
	double deltaDistX;
	double deltaDistY;
	t_game *game = (t_game *)g;
	while (!done)
	{
		i = 0;
		do_action(game);
		while (i < WINDOW_WIDTH)
		{
			double cameraX = 2 * (i - WINDOW_WIDTH/2) / ((double)(WINDOW_WIDTH)-1); // x-coordinate in camera space
			double rayDirX = game->camera->dirX + game->camera->planeX * cameraX;
			double rayDirY = game->camera->dirY + game->camera->planeY * cameraX;
			int mapx = (int)game->player->posX;
			int mapy = (int)game->player->posY;
			deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
			deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
			//exit(0);
			double perpWallDist;

			// what direction to step in x or y-direction (either +1 or -1)
			double stepX;
			double stepY;

			int hit = 0; // was there a wall hit?
			int side;	 // was a NS or a EW wall hit?
			// calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (game->player->posX - mapx) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapx + 1.0 - game->player->posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (game->player->posY - mapy) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapy + 1.0 - game->player->posY) * deltaDistY;
			}
			while (hit == 0)
			{
				// jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapx += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapy += stepY;
					side = 1;
				}
				// Check if ray has hit a wall
				// if((int)game->player->posX > game->config->mapMaxWidth || (int)game->player->posY > game->config->mapMaxHeight)
				//	exit(0);
				if (game->map[mapy][mapx] == '1')
					hit = 1;
			}
			if (side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			// Calculate height of line to draw on screen
			int lineHeight = (int)((WINDOW_HEIGHT - 200) / perpWallDist);
			// calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + (WINDOW_HEIGHT - 200) / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + (WINDOW_HEIGHT - 200) / 2;
			if (drawEnd >= (WINDOW_HEIGHT - 200))
				drawEnd = (WINDOW_HEIGHT - 200) - 1;
			int color = 0x000000ff;
			if (side == 1)
				color = color / 2;

			int start_end[2];
			start_end[0] = drawStart;
			start_end[1] = drawEnd;
			ft_verline(i, start_end, game, color);
			i++;
		}
		// render_frame2D(game);
		done = 1;
	}
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
	if (kc == 1)
	{
		game->player->health += 10;
		ft_draw_lifebar(game);
	}
//	printf("%d\n", kc);
	return (0);
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
	img.img = mlx_new_image(&mlxp, 1, WINDOW_HEIGHT - 200);
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
	// game.config->caseWidth = game.config->caseHeight;
	// load_textures(&game);
	// int i = 0;
	// printf("%p", (game.textures->wallText));
	// printf("\n");
	// 	uint32_t *val = (uint32_t *) game.textures->wallText;
	// while(i < 30)
	// {
	// 	printf("%d\n", ((uint32_t *)game.textures->wallText)[i]);
	// 	i++;
	//
	ft_draw_lifebar(&game);
	player_setpos(game.map, game.player);
// TODO Comprendre pourquoi la mouse_hook fait segfault je devienne fou
//	mlx_mouse_hook(mlxp.win_ptr, get_hp, &game);
	mlx_hook(mlxp.win_ptr, 2, 0, key_hook, &game);
	mlx_hook(mlxp.win_ptr, 3, 0, key_relase, &game);
	mlx_loop_hook(mlxp.mlx_ptr, (void *)drawRays3D, &game);
	// mlx_hook(e.win, 2, (1L << 0), &key_press, &e);
	// mlx_loop_hook(mlxp.mlx_ptr, (void *)render_frame2D, &game);
	// printf("%f %f\n", game.player->posX, game.player->posY);
	mlx_loop(mlxp.mlx_ptr);
}
