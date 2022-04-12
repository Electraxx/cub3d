#include "../headers/cub3d.h"

unsigned int get_pixel_color(int x, int y, char *firstpixel)
{
	unsigned int *fp;;

	fp = (unsigned int *)firstpixel;
	return (fp[y * 64 + x]);
}

void    set_pixel_color(int x, int y, char *firstpixel, unsigned int newVal)
{
	unsigned int *fp;;

	fp = (unsigned int *)firstpixel;
	fp[y * 64 + x] = newVal;
}


int *load_line_texture(int len, int step, int texPos, int texX, int side, t_image *texture)
{
	int        *lineText;
	int        i;
	int        texY;
	uint32_t   color;

	i = 0;
	lineText = malloc(sizeof(int) * (len + 1));
	while(i < len)
	{
		texY = (int)texPos & (64 - 1);
		texPos += step;
		color = get_pixel_color(texX, texY, texture->addr);
		if(side == 1)
			color = (color >> 1) & 8355711;
		lineText[i] = color;
		i++;
	}
	lineText[i] = 0;
	return (lineText);
}

t_image *get_texture(char c, t_assets *text)
{
	if (c == 'W')
		return (text->W_texture);
	else if (c == 'E')
		return (text->E_texture);
	else if (c == 'N')
		return (text->N_texture);
	else if (c == 'S')
		return (text->S_texture);
	else
		return (NULL);
}

void ft_temp(int drawStart, int y,char c, double step, int drawEnd, int side, uint32_t *textswag, int texX, double *texPos, t_image *text, int texY)
{

	uint32_t color = get_pixel_color(texX, texY, text->addr);

	if(side == 1) {
		color = (color >> 1) & 8355711;
	}
	*textswag = color;
	*texPos += step;//THIS|||
//    if(side == 1) {
//        *color = (*color >> 1) & 8355711;
//    }
//
//    textswag[y - drawStart] = *color;
   //int *textLine = load_line_texture(lineHeight, step, texPos, texX, side, texture);
	/*ft_verline(i, drawStart, game, textLine, drawEnd - drawStart);*/

//        if(side == 1)
//            *color = (*color >> 1) & 8355711;
//        //buffer[y][i] = color;
//        *textswag[y - drawStart] = *color;
		//my_mlx_pixel_put(game->buffer, y, 0, color);
	//}
	//textswag[y - drawStart] = 0;
}

t_image *get_ray_texture(t_game *game, int side, double rayDirX, double rayDirY)
{
	if(side)
	{
		if(rayDirY < 0)
			return (get_texture('N', game->textures));
		else
			return (get_texture('S', game->textures));
	}
	else
	{
		if(rayDirX < 0)
			return (get_texture('W', game->textures));
		else
			return (get_texture('E', game->textures));
	}
}

void raycast(t_raycast_data *rayData, t_camera *camera, double posX, double posY, char **map)
{
	//START INIT FUNC
	rayData->cameraX = 2 * (i - WINDOW_WIDTH/2) / ((double)(WINDOW_WIDTH)-1);
	rayData->rayDirY = camera->dirY + camera->planeY * rayData->cameraX;
	rayData->rayDirX = camera->dirX + camera->planeX * rayData->cameraX;
	rayData->mapX = (int) posX;
	rayData->mapY = (int) posY;
	rayData->deltaDistX = (rayData->rayDirX == 0) ? 1e30 : fabs(1 / rayData->rayDirX);
	rayData->deltaDistY = (rayData->rayDirY == 0) ? 1e30 : fabs(1 / rayData->rayDirY);
	rayData->hit = 0;
	//END INIT FUNC
	//SOME FUNC IDK HOW TO NAME IT LOL
	if (rayData->rayDirX < 0)
	{
		rayData->stepX = -1;
		rayData->sideDistX = (posX - rayData->mapX) * rayData->deltaDistX;
	}
	else
	{
		rayData->stepX = 1;
		rayData->sideDistX = (rayData->mapX + 1.0 - posX) * rayData->deltaDistX;
	}
	if (rayData->rayDirY < 0)
	{
		rayData->stepY = -1;
		rayData->sideDistY = (posY - rayData->mapY) * rayData->deltaDistY;
	}
	else
	{
		rayData->stepY = 1;
		rayData->sideDistY = (rayData->mapY + 1.0 - posY) * rayData->deltaDistY;
	}
	//END OF THAT ONE FUNC NOBODY CARES ABOUT
	//TODO func is_hit()
	while (rayData->hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (rayData->sideDistX < rayData->sideDistY)
		{
			rayData->sideDistX += rayData->deltaDistX;
			rayData->mapX += rayData->stepX;
			rayData->side = 0;
		}
		else
		{
			rayData->sideDistY += rayData->deltaDistY;
			rayData->mapY += rayData->stepY;
			rayData->side = 1;
		}
		// Check if ray has hit a wall
		if (map[rayData->mapY][rayData->mapX] == '1')
			rayData->hit = 1;
	}
	//END IS_HIT()
	//start func calculate_line()
	if (rayData->side == 0)
		rayData->line_data.perpWallDist = (rayData->sideDistX - rayData->deltaDistX);
	else
		rayData->line_data.perpWallDist = (rayData->sideDistY - rayData->deltaDistY);
	// Calculate height of line to draw on screen
	rayData->line_data.lineHeight = (int)((WINDOW_HEIGHT) / rayData->line_data.perpWallDist);
	// calculate lowest and highest pixel to fill in current stripe
	rayData->line_data.drawStart = -rayData->line_data.lineHeight / 2 + (WINDOW_HEIGHT) / 2;
	if (rayData->line_data.drawStart < 0)
		rayData->line_data.drawStart = 0;
	rayData->line_data.drawEnd = rayData->line_data.lineHeight / 2 + (WINDOW_HEIGHT) / 2;
	if (rayData->line_data.drawEnd >= (WINDOW_HEIGHT))
		rayData->line_data.drawEnd = (WINDOW_HEIGHT) - 1;
	//end func calculate_line()
	//START TEXTURE HANDLING I HAVE NOT A CLEAR IDEA ABOUT ON HOW TO SPLIT IT :))))))))))))))))))))))))))))))))))))
	//TODO TEXTURE HANDLING (starting at line 195)
	//END TEXTURE HANDLING
}

void    draw_view(t_raycast_data *rayData, t_camera *camera)
{
	int i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		raycast(rayData, camera);
		//exit(0);
		double perpWallDist;

		// what direction to step in x or y-direction (either +1 or -1)
		double stepX;
		double stepY;
		int hit = 0; // was there a wall hit?
		int side;	 // was a NS or a EW wall hit?
		// calculate step and initial sideDist
		char c;

		//DOWN HERE |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = game->player->posY + perpWallDist * rayDirY;
		else
			wallX = game->player->posX + perpWallDist * rayDirX;
		wallX -= floor(wallX);

		//x coordinate on the texture
		int texX = (int)(wallX * (64.0));
		if((side == 0 && rayDirX > 0) || (side == 1 && rayDirY < 0))
			texX = 64 - texX - 1;

		// How much to increase the texture coordinate per screen pixel
		double step = 1.0 * 64.0 / lineHeight;
		// Starting texture coordinate
		double texPos = (drawStart - WINDOW_HEIGHT / 2 + lineHeight / 2) * step;
		uint32_t *textswag = malloc(sizeof(uint32_t) * (drawEnd - drawStart + 1));
		//t_image *text = get_texture(c, game->textures);
		t_image *text = get_ray_texture(game, side, rayDirX, rayDirY);
		int y = drawStart;
		for(; y<drawEnd; y++) {
			// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
			int texY = (int) texPos & (64 - 1);
			uint32_t *test = &textswag[y - drawStart];

			ft_temp(drawStart, drawStart, c, step, drawEnd, side, test, texX, &texPos, text, texY);
		}
		textswag[y - drawStart] = 0;
		//load2()
		ft_verline(i, drawStart, game, textswag, lineHeight);
		i++;
	}
}

void drawRays3D(void *g)
{
	int				i;
	t_game			*game;
	t_raycast_data  rayData;

	i = 0;
	game = (t_game *) g;
	do_action(game);
	draw_view(&rayData);
	ft_draw_lifebar(game);
	//mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->buffer->img, 0, 0);
}

void ft_verline(int line, int start, t_game *game, uint32_t *colors, int lineHeight)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if(start < 0)
		exit(0);
	while (i < start)
	{
		my_mlx_pixel_put(game->buffer, 0, i, 0x00ff0000);
		i++;
	}
	while (colors[j])
	{
		my_mlx_pixel_put(game->buffer, 0, i, colors[j]);
		j++;
		i++;
	}
	while (i < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(game->buffer, 0, i, 0x0000ff00);
		i++;
	}
	mlx_put_image_to_window(game->mlxp->mlx_ptr, game->mlxp->win_ptr, game->buffer->img, line, 0);
	free(colors);
}