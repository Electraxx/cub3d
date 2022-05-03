/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:02:41 by vvermot-          #+#    #+#             */
/*   Updated: 2022/05/03 16:02:42 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	load_text_line(t_raycast_data *rayData, t_image *text)
{
	int					y;
	t_line_texture_data	*t_data;
	uint32_t			color;

	y = rayData->line_data.drawStart;
	t_data = &rayData->line_data.line_text_data;
	while (y < rayData->line_data.drawEnd)
	{
		t_data->texY = (int) t_data->texPos & (64 - 1);
		color = get_pixel_color(t_data->texX, t_data->texY, text->addr);
		if (rayData->side == 1)
			color = (color >> 1) & 8355711;
		t_data->pixelArray[y - rayData->line_data.drawStart] = color;
		t_data->texPos += rayData->line_data.line_text_data.step;
		y++;
	}
	t_data->pixelArray[y - rayData->line_data.drawStart] = 0;
}

void	init_ray(t_raycast_data *rayData, t_camera *camera, t_point pos)
{
	rayData->cameraX = 2 * (rayData->line - W_W / 2) / ((double)(W_W) - 1);
	rayData->rayDirY = camera->dirY + camera->planeY * rayData->cameraX;
	rayData->rayDirX = camera->dirX + camera->planeX * rayData->cameraX;
	rayData->mapX = (int) pos.x;
	rayData->mapY = (int) pos.y;
	if (rayData->rayDirX == 0)
		rayData->deltaDistX = 1e30;
	else
		rayData->deltaDistX = fabs(1 / rayData->rayDirX);
	if (rayData->rayDirY == 0)
		rayData->deltaDistY = 1e30;
	else
		rayData->deltaDistY = fabs(1 / rayData->rayDirY);
	rayData->hit = 0;
}

void	draw_view(t_raycast_data *rdata, t_game *game)
{
	rdata->line = -1;
	rdata->line_data.line_text_data.pixelArray
		= malloc(sizeof(uint32_t) * (W_H + 1));
	while (++rdata->line <= W_W)
	{
		init_ray(rdata, &game->camera, game->player.pos);
		calc_sidedist(rdata, game->player.pos);
		check_hit(rdata, game->map);
		calc_line(rdata);
		load_line(rdata, game->player.pos, game);
		verline(rdata, &game->coll_buffer, &game->mlxp, &game->config);
	}
	free(rdata->line_data.line_text_data.pixelArray);
}

void	draw(void *g)
{
	t_game			*game;
	t_raycast_data	ray_data;

	game = (t_game *) g;
	do_action(game);
	draw_view(&ray_data, game);
	ft_draw_lifebar(game);
}

void	verline(t_raycast_data *rdata, t_image *buf, t_mlxp *mlx, t_config *cfg)
{
	int			i;
	int			j;
	uint32_t	*pxline;

	i = 0;
	j = 0;
	pxline = rdata->line_data.line_text_data.pixelArray;
	while (i < rdata->line_data.drawStart)
	{
		my_mlx_pixel_put(buf, 0, i, cfg->ceiling);
		i++;
	}
	while (rdata->line_data.line_text_data.pixelArray[j])
	{
		my_mlx_pixel_put(buf, 0, i, pxline[j]);
		j++;
		i++;
	}
	while (i < W_H)
	{
		my_mlx_pixel_put(buf, 0, i, cfg->floor);
		i++;
	}
	mlx_put_image_to_window
		(mlx->mlx_ptr, mlx->win_ptr, buf->img, rdata->line, 0);
}
