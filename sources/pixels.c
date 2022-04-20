#include "../headers/cub3d.h"

unsigned int	get_pixel_color(int x, int y, char *firstpixel)
{
	unsigned int	*fp;

	fp = (unsigned int *)firstpixel;
	return (fp[y * 64 + x]);
}

void	set_pixel_color(int x, int y, char *firstpixel, unsigned int newVal)
{
	unsigned int	*fp;

	fp = (unsigned int *)firstpixel;
	fp[y * 64 + x] = newVal;
}

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->ll + x * (image->bpp / 8));
	*(unsigned int*)dst = color;
}