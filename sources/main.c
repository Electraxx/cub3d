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
	while (i < conf->caseHeight)
	{
		j = 0;
		while (j < conf->caseWidth)
		{
			my_mlx_pixel_put(game->buffer, j + (posX * conf->caseWidth), i + (posY * conf->caseHeight), color);
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
	// sleep(1);
	mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->buffer->img, 0, 0);
	//ft_print_map(game->map);
	//exit(0)
	return (0);
}

unsigned long createRGBA(t_color color)
{   
    return ((color.r & 0xff) << 24) + ((color.g & 0xff) << 16) + ((color.b & 0xff) << 8)
           + (color.a & 0xff);
}

void	ft_verline(int line, int *drawStart_end, t_game *game, int color)
{
	int	i;

	i = 0;
	// game->buffer->img = mlx_new_image(game->mlxp->mlx_ptr, 1, drawStart_end[1] - drawStart_end[0]);
	//game->buffer->addr = mlx_get_data_addr(game->buffer->img, &game->buffer->bits_per_pixel, &game->buffer->line_length,
								// &game->buffer->endian);
	while(i < drawStart_end[0])
	{
		my_mlx_pixel_put(game->buffer, 0, i, 0x00ff0000);
		i++;
	}
	while(i < drawStart_end[1])
	{
		my_mlx_pixel_put(game->buffer, 0, i, color);
		i++;
	}
	while(i < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(game->buffer, 0, i, 0x0000ff00);
		i++;
	}
	mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->buffer->img, line, 0);
}

void drawRays3D(void *g)
{
	int done = 0;
	int i = 0;
	double sideDistX;
	double sideDistY;
	double perpWallDist;
	double deltaDistX;
	double deltaDistY;
	t_game *game = (t_game *) g;
	while (!done)
	{
		i = 0;
		//usleep(100);
		while (i < WINDOW_WIDTH)
		{
			double cameraX = 2 * i / ((double)WINDOW_WIDTH - 1); //x-coordinate in camera space
			double rayDirX = game->camera->dirX + game->camera->planeX * cameraX;
			double rayDirY = game->camera->dirY + game->camera->planeY * cameraX;
			int mapx = (int) game->player->posX;
			int mapy = (int) game->player->posY;
			deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
			deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

			double perpWallDist;

			//what direction to step in x or y-direction (either +1 or -1)
			double stepX;
			double stepY;

			int hit = 0; //was there a wall hit?
			int side;	 //was a NS or a EW wall hit?
			//calculate step and initial sideDist
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
				//jump to next map square, either in x-direction, or in y-direction
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
				//Check if ray has hit a wall
				//if((int)game->player->posX > game->config->mapMaxWidth || (int)game->player->posY > game->config->mapMaxHeight)
				//	exit(0);
				if (game->map[mapy][mapx] == '1')
					hit = 1;
			}
			if (side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);
			//Calculate height of line to draw on screen
			int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);
			if (perpWallDist == 0)
				lineHeight = WINDOW_HEIGHT - 1;
			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
			if (drawEnd >= WINDOW_HEIGHT)
				drawEnd = WINDOW_HEIGHT - 1;

			//choose wall color
			//t_color color;
			//color.g = 255;
			int color = 0x000000ff;
			if (side == 1) {color = color / 2;}

			int start_end[2];
			start_end[0] = drawStart;
			start_end[1] = drawEnd;
      		//draw the pixels of the stripe as a vertical line
      		ft_verline(i, start_end, game, color);
			i++;
			}
			done = 1;
		}
}

/*int render_frame(void *g)
{
	t_game *game = (t_game *) g;
	double camX ;
	int w = 100;
	int i = 0;
	int j = 0;
	int planeX;
	int planeX;
	int rayDirX;
	int rayDirY;
  	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	while(i < w)
	{
		camX = 2 * game->player->posX / (double) w - 1;
		//double rayDirX = dirX + planeX * camX;
      	//double rayDirY = dirY + planeY * camX;
		i++;
	}
	return (0);
}*/

int main(int argc, char **argv)
{
	t_mlxp mlxp;
	t_cardi_check cardiCheck;
	t_game game;
	t_image img;
	game.player = malloc(sizeof(t_player));
	game.player->v_angle = 0;
	game.config = malloc(sizeof(t_config));
	game.camera = malloc(sizeof(t_camera));
	game.mlxp = &mlxp;
	game.buffer = &img;
	if (argc != 2)
		return (1);
	init_cardi_struct(&cardiCheck);
	ft_parse_file(argv[1], &cardiCheck, &game);
	fill_map(&game.map);
	ft_print_map(game.map);
	mlxp.mlx_ptr = mlx_init();
	mlxp.win_ptr = mlx_new_window(mlxp.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3d");
	img.img = mlx_new_image(&mlxp, 1, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	//draw_map(mlx, game);
	game.camera->dirX = -1;
	game.camera->dirY = 0;
	game.camera->planeX = 0;
	game.camera->planeY = 0.8;
	game.config->caseWidth = 64;
	game.config->mapMaxHeight = max_height(game.map);

	game.config->caseHeight = 64;
	game.config->mapMaxWidth = max_width(game.map);
	// game.config->caseWidth = game.config->caseHeight;
	player_setpos(game.map, game.player);
	int trash[2];

	/*trash[0] = 100;
	trash[1] = 300;
	t_color trash2;
	int j = 0;
	for (int i = 0; j < 20 ; i += 12)
	{
		ft_verline(300 + i, trash, &game, trash2);
		j++;
	}*/
	mlx_loop_hook(mlxp.mlx_ptr, (void *)drawRays3D, &game);
	printf("%f %f\n", game.player->posX, game.player->posY);
	mlx_key_hook(mlxp.win_ptr, key_hook, &game);
	mlx_loop(mlxp.mlx_ptr);
}
