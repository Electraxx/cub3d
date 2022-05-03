#include "../headers/cub3d.h"

void	calc_sidedist(t_raycast_data *rdata, t_point pos)
{
	if (rdata->rayDirX < 0)
	{
		rdata->stepX = -1;
		rdata->sideDistX = (pos.x - rdata->mapX) * rdata->deltaDistX;
	}
	else
	{
		rdata->stepX = 1;
		rdata->sideDistX = (rdata->mapX + 1.0 - pos.x) * rdata->deltaDistX;
	}
	if (rdata->rayDirY < 0)
	{
		rdata->stepY = -1;
		rdata->sideDistY = (pos.y - rdata->mapY) * rdata->deltaDistY;
	}
	else
	{
		rdata->stepY = 1;
		rdata->sideDistY = (rdata->mapY + 1.0 - pos.y) * rdata->deltaDistY;
	}
}

void	check_hit(t_raycast_data *rayData, char **map)
{
	while (rayData->hit == 0)
	{
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
		if (map[rayData->mapY][rayData->mapX] == '1')
			rayData->hit = 1;
	}
}

void	calc_line(t_raycast_data *rayData)
{
	t_line_data	*l_data;

	l_data = &rayData->line_data;
	if (rayData->side == 0)
		l_data->perpWallDist = (rayData->sideDistX - rayData->deltaDistX);
	else
		l_data->perpWallDist = (rayData->sideDistY - rayData->deltaDistY);
	l_data->lineHeight = (int)((W_H) / l_data->perpWallDist);
	l_data->drawStart = -l_data->lineHeight / 2 + (W_H) / 2;
	if (l_data->drawStart < 0)
		l_data->drawStart = 0;
	l_data->drawEnd = l_data->lineHeight / 2 + (W_H) / 2;
	if (l_data->drawEnd >= (W_H))
		l_data->drawEnd = (W_H) - 1;
}

void	load_line(t_raycast_data *rayData, t_point pos, t_game *game)
{
	t_line_texture_data	*text_data;
	t_line_data			*l_data;
	t_image				*texture;

	text_data = &rayData->line_data.line_text_data;
	l_data = &rayData->line_data;
	if (rayData->side == 0)
		text_data->wallX = pos.y + l_data->perpWallDist * rayData->rayDirY;
	else
		text_data->wallX = pos.x + l_data->perpWallDist * rayData->rayDirX;
	text_data->wallX -= floor(text_data->wallX);
	text_data->texX = (int)(text_data->wallX * (64.0));
	if ((rayData->side == 0 && rayData->rayDirX > 0)
		|| (rayData->side == 1 && rayData->rayDirY < 0))
		text_data->texX = 64 - text_data->texX - 1;
	text_data->step = 1.0 * 64.0 / l_data->lineHeight;
	text_data->texPos = (l_data->drawStart - W_H / 2 + l_data->lineHeight / 2)
		* text_data->step;
	texture = get_ray_texture(&game->textures, rayData);
	load_text_line(rayData, texture);
}
