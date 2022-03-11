#include "../headers/cub3d.h"

void	ft_print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
        write(1, map[i], ft_strlen(map[i]));
        write(1, "\n", 1);
		i++;
	}
}