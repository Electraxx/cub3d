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

void load_text_line(t_raycast_data *rayData, t_image *text)
{
	int					y;
	t_line_texture_data *t_data;

	y = rayData->line_data.drawStart;
	t_data = &rayData->line_data.line_text_data;
	t_data->pixelArray = malloc(sizeof(uint32_t) * (rayData->line_data.lineHeight + 1));
	while (y < rayData->line_data.drawEnd)
	{
		t_data->texY = (int) t_data->texPos & (64 - 1);
		uint32_t color = get_pixel_color(t_data->texX, t_data->texY, text->addr);
		if(rayData->side == 1) {
			color = (color >> 1) & 8355711;
		}
		t_data->pixelArray[y - rayData->line_data.drawStart] = color;
		t_data->texPos += rayData->line_data.line_text_data.step;
		y++;
	}
	t_data->pixelArray[y - rayData->line_data.drawStart] = 0;
}

t_image *get_ray_texture(t_assets *assets, t_raycast_data *rdata)
{
	if(rdata->side)
	{
		if(rdata->rayDirY < 0)
			return (get_texture('N', assets));
		else
			return (get_texture('S', assets));
	}
	else
	{
		if(rdata->rayDirX < 0)
			return (get_texture('W', assets));
		else
			return (get_texture('E', assets));
	}
}

void init_ray(t_raycast_data *rayData, t_camera *camera, t_point pos)
{
	rayData->cameraX = 2 * (rayData->line - WINDOW_WIDTH / 2) / ((double) (WINDOW_WIDTH) - 1);
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

void check_hit(t_raycast_data *rayData, char **map)
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
	t_line_data *l_data;

	l_data = &rayData->line_data;
	if (rayData->side == 0)
		l_data->perpWallDist = (rayData->sideDistX - rayData->deltaDistX);
	else
		l_data->perpWallDist = (rayData->sideDistY - rayData->deltaDistY);
	l_data->lineHeight = (int) ((WINDOW_HEIGHT) / l_data->perpWallDist);
	l_data->drawStart = -l_data->lineHeight / 2 + (WINDOW_HEIGHT) / 2;
	if (l_data->drawStart < 0)
		l_data->drawStart = 0;
	l_data->drawEnd = l_data->lineHeight / 2 + (WINDOW_HEIGHT) / 2;
	if (l_data->drawEnd >= (WINDOW_HEIGHT))
		l_data->drawEnd = (WINDOW_HEIGHT) - 1;
}

void load_line(t_raycast_data *rayData, t_point pos,t_game *game)
{
	t_line_texture_data *text_data;
	t_line_data 		*l_data;
	t_image 			*texture;

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
	texture = get_ray_texture(game->textures, rayData);
	load_text_line(rayData, texture);
}

void draw_view(t_raycast_data *rdata, t_game *game)
{
	rdata->line = -1;
	while(++rdata->line <= WINDOW_WIDTH) {
		init_ray(rdata, game->camera, game->player->pos);
		calc_sideDist(rdata, game->player->pos);
		check_hit(rdata, game->map);
		calc_line(rdata);
		load_line(rdata, game->player->pos, game);
		ft_verline(rdata, game->buffer, game->mlxp, game->config);
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

void ft_verline(t_raycast_data *rdata, t_image *buffer,t_mlxp *mlx, t_config *cfg)
{
	int i;
	int j;
	uint32_t *pxline;

	i = 0;
	j = 0;
	pxline = rdata->line_data.line_text_data.pixelArray;
	while (i < rdata->line_data.drawStart)
	{
		my_mlx_pixel_put(buffer, 0, i, cfg->ceiling);
		i++;
	}
	while (rdata->line_data.line_text_data.pixelArray[j])
	{
		my_mlx_pixel_put(buffer, 0, i, pxline[j]);
		j++;
		i++;
	}
	while (i < WINDOW_HEIGHT)
	{
		my_mlx_pixel_put(buffer, 0, i, cfg->floor);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, buffer->img, rdata->line, 0);
	free(rdata->line_data.line_text_data.pixelArray);
}