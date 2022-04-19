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

void ft_temp(double step, int drawEnd, int side, uint32_t *textswag, int texX, double *texPos, t_image *text, int texY)
{

	uint32_t color = get_pixel_color(texX, texY, text->addr);

	if(side == 1) {
		color = (color >> 1) & 8355711;
	}
	*textswag = color;
	*texPos += step;//THIS|||
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

void init_ray(t_raycast_data *rayData, t_camera *camera, int line, double posX, double posY)
{
	rayData->cameraX = 2 * (line - WINDOW_WIDTH / 2) / ((double) (WINDOW_WIDTH) - 1);
	rayData->rayDirY = camera->dirY + camera->planeY * rayData->cameraX;
	rayData->rayDirX = camera->dirX + camera->planeX * rayData->cameraX;
	rayData->mapX = (int) posX;
	rayData->mapY = (int) posY;
	rayData->deltaDistX = (rayData->rayDirX == 0) ? 1e30 : fabs(1 / rayData->rayDirX);
	rayData->deltaDistY = (rayData->rayDirY == 0) ? 1e30 : fabs(1 / rayData->rayDirY);
	rayData->hit = 0;
}

void calc_sideDist(t_raycast_data *rdata, double posX, double posY)
{
	if (rdata->rayDirX < 0) {
		rdata->stepX = -1;
		rdata->sideDistX = (posX - rdata->mapX) * rdata->deltaDistX;
	} else {
		rdata->stepX = 1;
		rdata->sideDistX = (rdata->mapX + 1.0 - posX) * rdata->deltaDistX;
	}
	if (rdata->rayDirY < 0) {
		rdata->stepY = -1;
		rdata->sideDistY = (posY - rdata->mapY) * rdata->deltaDistY;
	} else {
		rdata->stepY = 1;
		rdata->sideDistY = (rdata->mapY + 1.0 - posY) * rdata->deltaDistY;
	}
}

void check_hit(t_raycast_data *rayData, char **map) //TODO make it return an int and check it directly
{
	while (rayData->hit == 0) {
		// jump to next map square, either in x-direction, or in y-direction
		if (rayData->sideDistX < rayData->sideDistY) {
			rayData->sideDistX += rayData->deltaDistX;
			rayData->mapX += rayData->stepX;
			rayData->side = 0;
		} else {
			rayData->sideDistY += rayData->deltaDistY;
			rayData->mapY += rayData->stepY;
			rayData->side = 1;
		}
		// Check if ray has hit a wall
		if (map[rayData->mapY][rayData->mapX] == '1')
			rayData->hit = 1;
	}
}

void calc_line(t_raycast_data *rayData)
{
	if (rayData->side == 0)
		rayData->line_data.perpWallDist = (rayData->sideDistX - rayData->deltaDistX);
	else
		rayData->line_data.perpWallDist = (rayData->sideDistY - rayData->deltaDistY);
	rayData->line_data.lineHeight = (int) ((WINDOW_HEIGHT) / rayData->line_data.perpWallDist);
	rayData->line_data.drawStart = -rayData->line_data.lineHeight / 2 + (WINDOW_HEIGHT) / 2;
	if (rayData->line_data.drawStart < 0)
		rayData->line_data.drawStart = 0;
	rayData->line_data.drawEnd = rayData->line_data.lineHeight / 2 + (WINDOW_HEIGHT) / 2;
	if (rayData->line_data.drawEnd >= (WINDOW_HEIGHT))
		rayData->line_data.drawEnd = (WINDOW_HEIGHT) - 1;
}

void load_line(t_raycast_data *rdata)
{

}

void raycast(t_raycast_data *rayData, t_camera *camera, double posX, double posY, char **map, t_game *game)
{
	int i;

	i = 0;
	while(i < WINDOW_WIDTH) {
		init_ray(rayData, camera, i, game->player->posX, game->player->posY);
		calc_sideDist(rayData, posX, posY);
		check_hit(rayData, game->map);
		calc_line(rayData);
		//START TEXTURE HANDLING I HAVE NOT A CLEAR IDEA ABOUT ON HOW TO SPLIT IT :))))))))))))))))))))))))))))))))))))
		if (rayData->side == 0)
			rayData->line_data.line_text_data.wallX = posY + rayData->line_data.perpWallDist * rayData->rayDirY;
		else
			rayData->line_data.line_text_data.wallX = posX + rayData->line_data.perpWallDist * rayData->rayDirX;
		rayData->line_data.line_text_data.wallX -= floor(rayData->line_data.line_text_data.wallX);

		rayData->line_data.line_text_data.texX = (int) (rayData->line_data.line_text_data.wallX * (64.0));
		if ((rayData->side == 0 && rayData->rayDirX > 0) || (rayData->side == 1 && rayData->rayDirY < 0))
			rayData->line_data.line_text_data.texX = 64 - rayData->line_data.line_text_data.texX - 1;

		// How much to increase the texture coordinate per screen pixel
		rayData->line_data.line_text_data.step = 1.0 * 64.0 / rayData->line_data.lineHeight;
		// Starting texture coordinate
		rayData->line_data.line_text_data.texPos = (rayData->line_data.drawStart - WINDOW_HEIGHT / 2 + rayData->line_data.lineHeight / 2) * rayData->line_data.line_text_data.step;
		rayData->line_data.line_text_data.pixelArray = malloc(sizeof(uint32_t) * (rayData->line_data.drawEnd - rayData->line_data.drawStart + 1));
		t_image *text = get_ray_texture(game, rayData->side, rayData->rayDirX, rayData->rayDirY);

		int y = rayData->line_data.drawStart;
		uint32_t *textswag = malloc(sizeof(uint32_t) * (rayData->line_data.drawEnd - rayData->line_data.drawStart + 1));
		for(; y<rayData->line_data.drawEnd; y++) {
			rayData->line_data.line_text_data.texY = (int) rayData->line_data.line_text_data.texPos & (64 - 1);
			uint32_t *test = &textswag[y - rayData->line_data.drawStart];

			ft_temp(rayData->line_data.line_text_data.step, rayData->line_data.drawEnd, rayData->side, test, rayData->line_data.line_text_data.texX, &rayData->line_data.line_text_data.texPos, text, rayData->line_data.line_text_data.texY);
		}
		textswag[y - rayData->line_data.drawStart] = 0;
		ft_verline(i, rayData->line_data.drawStart, game, textswag, rayData->line_data.lineHeight);
		//END TEXTURE HANDLING
		i++;
	}
}

void    draw_view(t_raycast_data *rayData, t_camera *camera, t_game *game)
{
		raycast(rayData, camera, game->player->posX, game->player->posY, game->map, game);
}

void drawRays3D(void *g)
{
	int				i;
	t_game			*game;
	t_raycast_data  rayData;

	i = 0;
	game = (t_game *) g;
	do_action(game);
	draw_view(&rayData, game->camera, game);
	//ft_draw_lifebar(game);
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