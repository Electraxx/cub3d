/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:03:19 by vvermot-          #+#    #+#             */
/*   Updated: 2022/05/03 16:03:26 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	fix_png(t_image *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 64)
		{
			if (get_pixel_color(i, j, img->addr) == 4278190080)
				my_mlx_pixel_put(img, i, j, 0x00ffffff);
			j++;
		}
		i++;
	}
}

void	load_asset(t_image *asset, char *path, t_mlxp *mlxp)
{
	int	a;
	int	b;

	asset->img = mlx_xpm_file_to_image(mlxp->mlx_ptr, path, &a, &b);
	asset->addr = mlx_get_data_addr
		(asset->img, &asset->bpp, &asset->ll, &asset->endian);
	fix_png(asset);
}

void	load_textures(t_game *game)
{
	game->textures.s_texture = malloc(sizeof (t_image));
	game->textures.e_texture = malloc(sizeof (t_image));
	game->textures.w_texture = malloc(sizeof (t_image));
	game->textures.n_texture = malloc(sizeof (t_image));
	load_asset(game->textures.e_texture, game->config.path_ea, &game->mlxp);
	load_asset(game->textures.s_texture, game->config.path_so, &game->mlxp);
	load_asset(game->textures.n_texture, game->config.path_no, &game->mlxp);
	load_asset(game->textures.w_texture, game->config.path_we, &game->mlxp);
}

t_image	*get_ray_texture(t_assets *assets, t_raycast_data *rdata)
{
	if (rdata->side)
	{
		if (rdata->raydiry < 0)
			return (get_texture('N', assets));
		else
			return (get_texture('S', assets));
	}
	else
	{
		if (rdata->raydirx < 0)
			return (get_texture('W', assets));
		else
			return (get_texture('E', assets));
	}
}

t_image	*get_texture(char c, t_assets *text)
{
	if (c == 'W')
		return (text->w_texture);
	else if (c == 'E')
		return (text->e_texture);
	else if (c == 'N')
		return (text->n_texture);
	else if (c == 'S')
		return (text->s_texture);
	else
		return (NULL);
}
