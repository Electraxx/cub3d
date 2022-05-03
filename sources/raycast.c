/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:04:05 by vvermot-          #+#    #+#             */
/*   Updated: 2022/05/03 16:04:06 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	calc_sidedist(t_raycast_data *rdata, t_point pos)
{
	if (rdata->raydirx < 0)
	{
		rdata->stepx = -1;
		rdata->sidedistx = (pos.x - rdata->mapx) * rdata->deltadistx;
	}
	else
	{
		rdata->stepx = 1;
		rdata->sidedistx = (rdata->mapx + 1.0 - pos.x) * rdata->deltadistx;
	}
	if (rdata->raydiry < 0)
	{
		rdata->stepy = -1;
		rdata->sidedisty = (pos.y - rdata->mapy) * rdata->deltadisty;
	}
	else
	{
		rdata->stepy = 1;
		rdata->sidedisty = (rdata->mapy + 1.0 - pos.y) * rdata->deltadisty;
	}
}

void	check_hit(t_raycast_data *rayData, char **map)
{
	while (rayData->hit == 0)
	{
		if (rayData->sidedistx < rayData->sidedisty)
		{
			rayData->sidedistx += rayData->deltadistx;
			rayData->mapx += rayData->stepx;
			rayData->side = 0;
		}
		else
		{
			rayData->sidedisty += rayData->deltadisty;
			rayData->mapy += rayData->stepy;
			rayData->side = 1;
		}
		if (map[rayData->mapy][rayData->mapx] == '1')
			rayData->hit = 1;
	}
}

void	calc_line(t_raycast_data *rayData)
{
	t_line_data	*l_data;

	l_data = &rayData->line_data;
	if (rayData->side == 0)
		l_data->perpwalldist = (rayData->sidedistx - rayData->deltadistx);
	else
		l_data->perpwalldist = (rayData->sidedisty - rayData->deltadisty);
	l_data->lineheight = (int)((W_H) / l_data->perpwalldist);
	l_data->drawstart = -l_data->lineheight / 2 + (W_H) / 2;
	if (l_data->drawstart < 0)
		l_data->drawstart = 0;
	l_data->drawend = l_data->lineheight / 2 + (W_H) / 2;
	if (l_data->drawend >= (W_H))
		l_data->drawend = (W_H) - 1;
}

void	load_line(t_raycast_data *rayData, t_point pos, t_game *game)
{
	t_line_texture_data	*text_data;
	t_line_data			*l_data;
	t_image				*texture;

	text_data = &rayData->line_data.line_text_data;
	l_data = &rayData->line_data;
	if (rayData->side == 0)
		text_data->wallx = pos.y + l_data->perpwalldist * rayData->raydiry;
	else
		text_data->wallx = pos.x + l_data->perpwalldist * rayData->raydirx;
	text_data->wallx -= floor(text_data->wallx);
	text_data->texx = (int)(text_data->wallx * (64.0));
	if ((rayData->side == 0 && rayData->raydirx > 0)
		|| (rayData->side == 1 && rayData->raydiry < 0))
		text_data->texx = 64 - text_data->texx - 1;
	text_data->step = 1.0 * 64.0 / l_data->lineheight;
	text_data->texpos = (l_data->drawstart - W_H / 2 + l_data->lineheight / 2)
						* text_data->step;
	texture = get_ray_texture(&game->textures, rayData);
	load_text_line(rayData, texture);
}
