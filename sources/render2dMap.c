#include "../headers/cub3d.h"

/*void	set_background(t_mlxp p)
{
	int		i;
	int		j;
	int		a;
	int		b;
	void	*img;

	i = 0;
	while (p.map[i])
	{
		j = 0;
		while (p.map[i][j])
		{
			img = mlx_xpm_file_to_image(p.mlx_ptr, get_res_path('0'), &a, &b);
			//mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, img, j * 32, i * 32);
			j++;
		}
		i++;
	}
}*/

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	max_height(char **map)
{
	return ft_2dim_char_sz(map);
}

int	max_width(char **map)
{
	size_t	max;
	size_t	i;

	max = 0;
	i = 0;
	while(map[i])
	{
		if(ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return max;
}

/*void	draw_map(t_mlxp p, t_game game)
{
	int		k;
	int		j;
	void	*i;
	int		a;
	char	*r;

	k = 0;
	set_background(p);
	while (p.map[k])
	{
		j = 0;
		while (p.map[k][j])
		{
			r = get_res_path(p.map[k][j]);
			i = mlx_xpm_file_to_image(p.mlx_ptr, r, &a, &a);
			mlx_put_image_to_window(p.mlx_ptr, p.win_ptr, i, j * 32, k * 32);
			j++;
		}
		k++;
	}
}*/