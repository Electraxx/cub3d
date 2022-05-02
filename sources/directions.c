#include "../headers/cub3d.h"

char	get_adjacent_cardinal(int vec, char curr)
{
	char	*cardinal;
	int 	i;
	char 	ret;

	i = 0;
	cardinal = ft_strcpy("NESW");
	while (curr != cardinal[i])
		i++;
	i += vec;
	ret = cardinal[i % 4];
	free(cardinal);
	return ret;
}

//Default is W
void set_player_dir(t_camera *camera, char goal)
{
	double oldDirX;
	double oldPlaneX;
	char	curr;
	int 	i;

	curr = 'W';
	i = 0;
	while(curr != goal)
	{
		curr = get_adjacent_cardinal(1, curr);
		i++;
	}
	oldPlaneX = camera->planeX;
	oldDirX = camera->dirX;
	double rad = (i * -90) * (PI / 180);
	printf("i = %d rad \n", i);
	camera->dirX = oldDirX * cos(rad) - camera->dirY * sin(rad);
	camera->dirY = oldDirX * sin(rad) + camera->dirY * cos(rad);
	camera->planeX = camera->planeX * cos(rad) - camera->planeY * sin(rad);
	camera->planeY = oldPlaneX * sin(rad) + camera->planeY * cos(rad);
}

void get_player_orientation(char **map, t_config *cfg)
{
	int i;
	int j;
	char *cardi;
	char *tmp;

	i = 0;
	j = 0;
	cardi = ft_strcpy("NESW");
	while(map[i]) {
		j = 0;
		while (cardi[j])
		{
			tmp = ft_strchr(map[i], cardi[j]);
			if(tmp != NULL)
			{
				cfg->firstDir = tmp[0];
				free(cardi);
				return ;
			}
			j++;
		}
		i++;
	}
	free(cardi);
}