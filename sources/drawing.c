#include "../headers/cub3d.h"

void	load_text_line(t_raycast_data *rayData, t_image *text)
{
	int					y;
	t_line_texture_data	*t_data;
	uint32_t			color;

	y = rayData->line_data.drawstart;
	t_data = &rayData->line_data.line_text_data;
	while (y < rayData->line_data.drawend)
	{
		t_data->texy = (int) t_data->texpos & (64 - 1);
		color = get_pixel_color(t_data->texx, t_data->texy, text->addr);
		if (rayData->side == 1)
			color = (color >> 1) & 8355711;
		t_data->pixelarray[y - rayData->line_data.drawstart] = color;
		t_data->texpos += rayData->line_data.line_text_data.step;
		y++;
	}
	t_data->pixelarray[y - rayData->line_data.drawstart] = 0;
}

void	init_ray(t_raycast_data *rayData, t_camera *camera, t_point pos)
{
	rayData->camerax = 2 * (rayData->line - W_W / 2) / ((double)(W_W) - 1);
	rayData->raydiry = camera->diry + camera->planey * rayData->camerax;
	rayData->raydirx = camera->dirx + camera->planex * rayData->camerax;
	rayData->mapx = (int) pos.x;
	rayData->mapy = (int) pos.y;
	if (rayData->raydirx == 0)
		rayData->deltadistx = 1e30;
	else
		rayData->deltadistx = fabs(1 / rayData->raydirx);
	if (rayData->raydiry == 0)
		rayData->deltadisty = 1e30;
	else
		rayData->deltadisty = fabs(1 / rayData->raydiry);
	rayData->hit = 0;
}

void	draw_view(t_raycast_data *rdata, t_game *game)
{
	rdata->line = -1;
	rdata->line_data.line_text_data.pixelarray
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
	free(rdata->line_data.line_text_data.pixelarray);
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
	pxline = rdata->line_data.line_text_data.pixelarray;
	while (i < rdata->line_data.drawstart)
	{
		my_mlx_pixel_put(buf, 0, i, cfg->ceiling);
		i++;
	}
	while (rdata->line_data.line_text_data.pixelarray[j])
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
