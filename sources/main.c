#include "cub3d.h"

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

void	ft_verline(int line, int *drawStart_end, t_game *game, t_color color)
{
	int	i;
	t_image img;

	i = drawStart_end[0];
	img.img = mlx_new_image(game->mlxp, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	printf("0 : %d\n", drawStart_end[0]);
	printf("1 : %d\n", drawStart_end[1]);
	printf("line : %d\n", line);
	printf("rgbbb : %lu\n", createRGBA(color));
	//exit(0);
	while(i < drawStart_end[1])
	{
		my_mlx_pixel_put(&img, line, drawStart_end[0], 0x00ff0000);
		i++;
	}
	mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, img.img, line, drawStart_end[0]);
}

void drawRays3D(void *g)
{
	int w = 3;
	double dirX = -1, dirY = 0;		  //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
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
		while (i < w)
		{
			double cameraX = 2 * i / ((double)w - 1); //x-coordinate in camera space
			double rayDirX = dirX + planeX * cameraX;
			double rayDirY = dirY + planeY * cameraX;

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
				sideDistX = (game->player->posX - (int)game->player->posX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = ((int)game->player->posX + 1.0 - game->player->posX) * deltaDistX;
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (game->player->posY - (int)game->player->posY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = ((int)game->player->posY + 1.0 - game->player->posY) * deltaDistY;
			}

			while (hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					game->player->posX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					game->player->posY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				//if((int)game->player->posX > game->config->mapMaxWidth || (int)game->player->posY > game->config->mapMaxHeight)
				//	exit(0);
				if (game->map[(int)game->player->posY][(int)game->player->posX] > '0')
					hit = 1;
			}
			if(side == 0)
				perpWallDist = (sideDistX - deltaDistX);
			else
				perpWallDist = (sideDistY - deltaDistY);

			//Calculate height of line to draw on screen
			int lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);

			//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
			if (drawStart < 0)
				drawStart = 0;
			int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
			if (drawEnd >= WINDOW_HEIGHT)
				drawEnd = WINDOW_HEIGHT - 1;

			//choose wall color
			t_color color;
			color.g = 255;
			if(game->map[(int)game->player->posY][(int)game->player->posX] == '1')
				color.r = 255;
			int start_end[2];
			start_end[0] = drawStart;
			start_end[1] = drawEnd;
      		//draw the pixels of the stripe as a vertical line
      		ft_verline(i, start_end, game, color);
			i++;
			}
			//done = 1;
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
	game.mlxp = &mlxp;
	game.buffer = &img;
	(void)img;
	(void)argc;
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

	game.config->caseWidth = 64;
	game.config->mapMaxHeight = max_height(game.map);

	game.config->caseHeight = 64;
	game.config->mapMaxWidth = max_width(game.map);
	// game.config->caseWidth = game.config->caseHeight;
	player_setpos(game.map, game.player);
	mlx_loop_hook(mlxp.mlx_ptr, (void *)drawRays3D, &game);
	printf("%f %f\n", game.player->posX, game.player->posY);
	mlx_key_hook(mlxp.win_ptr, key_hook, &game);
	mlx_loop(mlxp.mlx_ptr);
	/*while(1)
	{
		printf("hahahahahah\n");
	}
	game_loop(&game, &mlxp, &img);*/
}
