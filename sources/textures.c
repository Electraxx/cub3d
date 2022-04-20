#include "../headers/cub3d.h"

void fix_png(t_image *img)
{
	int i;
	int j;

	i = 0;
	while(i < 64)
	{
		j = 0;
		while(j < 64)
		{
			if(get_pixel_color(i, j, img->addr) == 4278190080)
				set_pixel_color(i, j, img->addr, 0x00ffffff);
			j++;
		}
		i++;
	}
}

void load_asset(t_image *asset, char *path, t_mlxp *mlxp)
{
	int a;
	int b;

	asset->img = mlx_xpm_file_to_image(mlxp->mlx_ptr, path, &a, &b);
	asset->addr =  mlx_get_data_addr(asset->img, &asset->bpp, &asset->ll, &asset->endian);
	fix_png(asset);
}

void	load_textures(t_game *game)
{
	game->textures.S_texture = malloc(sizeof (t_image));
	game->textures.E_texture = malloc(sizeof (t_image));
	game->textures.W_texture = malloc(sizeof (t_image));
	game->textures.N_texture = malloc(sizeof (t_image));
	load_asset(game->textures.E_texture, "textures/flag.xpm", &game->mlxp);
	load_asset(game->textures.S_texture, "textures/wall.xpm", &game->mlxp);
	load_asset(game->textures.N_texture, "textures/roz.xpm", &game->mlxp);
	load_asset(game->textures.W_texture, "textures/mac64.xpm", &game->mlxp);

}