#include "../headers/cub3d.h"
void ft_draw_lifebar(t_game *game)
{
	int		j;
	int		i;

	i = 0;
	while (i < W_W / 3)
	{
		j = -1;
		while (++j < 30)
		{
			if (j < 5 || j > 25 || i < 5 || i > W_W / 3 - 5)
				my_mlx_pixel_put(&game->lifebar, i, j, 0x00ffffff);
			else if (i < game->player.health)
				my_mlx_pixel_put(&game->lifebar, i, j, 0x00ff0000);
			else
				my_mlx_pixel_put(&game->lifebar, i, j, 0x00000000);
		}
		i++;
	}
	mlx_put_image_to_window(game->mlxp.mlx_ptr, game->mlxp.win_ptr, game->lifebar.img, 10, W_H - 100); //TODO check
}

int get_hp(int kc, t_game *game)
{
//	if (kc == 1)
//	{
//		game->player->health += 10;
//		ft_draw_lifebar(game);
//	}
	printf("%d\n", kc);
	return (0);
}