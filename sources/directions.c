#include "../headers/cub3d.h"

char	get_adjacent_cardinal(int vec, char curr)
{
	char	*cardinal;
	int		i;
	char	ret;

	i = 0;
	cardinal = ft_strcpy("NESW");
	while (curr != cardinal[i])
		i++;
	i += vec;
	ret = cardinal[i % 4];
	free(cardinal);
	return (ret);
}

void	set_player_dir(t_camera *camera, char goal)
{
	double	old_dirx;
	double	old_planex;
	char	curr;
	int		i;
	double	rad;

	curr = 'W';
	i = 0;
	while (curr != goal)
	{
		curr = get_adjacent_cardinal(1, curr);
		i++;
	}
	old_planex = camera->planex;
	old_dirx = camera->dirx;
	rad = (i * -90) * (PI / 180);
	camera->dirx = old_dirx * cos(rad) - camera->diry * sin(rad);
	camera->diry = old_dirx * sin(rad) + camera->diry * cos(rad);
	camera->planex = camera->planex * cos(rad) - camera->planey * sin(rad);
	camera->planey = old_planex * sin(rad) + camera->planey * cos(rad);
}

void	get_player_orientation(char **map, t_config *cfg)
{
	int		i;
	int		j;
	char	*cardi;
	char	*tmp;

	i = 0;
	cardi = ft_strcpy("NESW");
	while (map[i])
	{
		j = 0;
		while (cardi[j])
		{
			tmp = ft_strchr(map[i], cardi[j]);
			if (tmp != NULL)
			{
				cfg->firstdir = tmp[0];
				free(cardi);
				return ;
			}
			j++;
		}
		i++;
	}
	free(cardi);
}
