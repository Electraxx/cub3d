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

void ft_temp(t_raycast_data *rayData, t_image *text)
{
	int y = rayData->line_data.drawStart;
	rayData->line_data.line_text_data.pixelArray = malloc(sizeof(uint32_t) * (rayData->line_data.lineHeight + 1));
	for(; y<rayData->line_data.drawEnd; y++)
	{
	rayData->line_data.line_text_data.texY = (int) rayData->line_data.line_text_data.texPos & (64 - 1);
	//uint32_t *test = &textswag[y - rayData->line_data.drawStart];



	uint32_t color = get_pixel_color(rayData->line_data.line_text_data.texX, rayData->line_data.line_text_data.texY, text->addr);

	if(rayData->side == 1) {
		color = (color >> 1) & 8355711;
	}
	rayData->line_data.line_text_data.pixelArray[y - rayData->line_data.drawStart] = color;
	rayData->line_data.line_text_data.texPos += rayData->line_data.line_text_data.step;
	}
	rayData->line_data.line_text_data.pixelArray[y - rayData->line_data.drawStart] = 0;
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

void init_ray(t_raycast_data *rayData, t_camera *camera, int line, t_point pos)
{
	rayData->cameraX = 2 * (line - WINDOW_WIDTH / 2) / ((double) (WINDOW_WIDTH) - 1);
	rayData->rayDirY = camera->dirY + camera->planeY * rayData->cameraX;
	rayData->rayDirX = camera->dirX + camera->planeX * rayData->cameraX;
	rayData->mapX = (int) pos.x;
	rayData->mapY = (int) pos.y;
	rayData->deltaDistX = (rayData->rayDirX == 0) ? 1e30 : fabs(1 / rayData->rayDirX);
	rayData->deltaDistY = (rayData->rayDirY == 0) ? 1e30 : fabs(1 / rayData->rayDirY);
	rayData->hit = 0;
}

void calc_sideDist(t_raycast_data *rdata, t_point pos)
{
	if (rdata->rayDirX < 0) {
		rdata->stepX = -1;
		rdata->sideDistX = (pos.x - rdata->mapX) * rdata->deltaDistX;
	} else {
		rdata->stepX = 1;
		rdata->sideDistX = (rdata->mapX + 1.0 - pos.x) * rdata->deltaDistX;
	}
	if (rdata->rayDirY < 0) {
		rdata->stepY = -1;
		rdata->sideDistY = (pos.y - rdata->mapY) * rdata->deltaDistY;
	} else {
		rdata->stepY = 1;
		rdata->sideDistY = (rdata->mapY + 1.0 - pos.y) * rdata->deltaDistY;
	}
}

void check_hit(t_raycast_data *rayData, char **map) //TODO make it return an int and check it directly
{
	while (rayData->hit == 0) {
		if (rayData->sideDistX < rayData->sideDistY) {
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

void load_line(t_raycast_data *rayData, t_point pos,t_game *game, int line)
{
	t_line_texture_data *text_data;
	t_line_data 		*l_data;

	text_data = &rayData->line_data.line_text_data;
	l_data = &rayData->line_data;
	if (rayData->side == 0)
		text_data->wallX = pos.y + l_data->perpWallDist * rayData->rayDirY;
	else
		text_data->wallX = pos.x + l_data->perpWallDist * rayData->rayDirX;
	text_data->wallX -= floor(text_data->wallX);
	text_data->texX = (int) (text_data->wallX * (64.0));
	if ((rayData->side == 0 && rayData->rayDirX > 0) || (rayData->side == 1 && rayData->rayDirY < 0))
		text_data->texX = 64 - text_data->texX - 1;
	text_data->step = 1.0 * 64.0 / l_data->lineHeight;
	text_data->texPos = (l_data->drawStart - WINDOW_HEIGHT / 2 + l_data->lineHeight / 2) * text_data->step;
	text_data->pixelArray = malloc(sizeof(uint32_t) * (l_data->drawEnd - l_data->drawStart + 1));
	t_image *text = get_ray_texture(game, rayData->side, rayData->rayDirX, rayData->rayDirY);
	ft_temp(rayData, text);
}

void draw_view(t_raycast_data *rdata, t_game *game)
{
	int 				i;
	t_line_data			*l_data;
	t_line_texture_data *text_data;


	i = -1;
	l_data = &rdata->line_data;
	text_data = &l_data->line_text_data;
	while(++i <= WINDOW_WIDTH) {
		init_ray(rdata, game->camera, i, game->player->pos);
		calc_sideDist(rdata, game->player->pos);
		check_hit(rdata, game->map);
		calc_line(rdata);
		load_line(rdata, game->player->pos, game, i);
		ft_verline(i, l_data->drawStart, game, text_data->pixelArray, l_data->lineHeight);
	}
}

void draw(void *g)
{
	t_game			*game;
	t_raycast_data  rayData;

	game = (t_game *) g;
	do_action(game);
	draw_view(&rayData, game);
	ft_draw_lifebar(game);
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