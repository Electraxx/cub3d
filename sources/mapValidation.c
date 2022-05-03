#include "../headers/cub3d.h"

static char	**ft_replace_spaces_with_1(char **map)
{
	int	j;
	int	i;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '1';
			j++;
		}
		i++;
	}
	return (map);
}

void	fill_map(char ***map)
{
	size_t	i;
	size_t	max;
	char	*tempstr;

	max = max_width(*map);
	i = 0;
	while ((*map)[i])
	{
		if (ft_strlen((*map)[i]) < max)
		{
			tempstr = ft_calloc((max + 1), sizeof(char));
			ft_bchar(tempstr, max, '1');
			ft_memcpy(tempstr, (*map)[i], ft_strlen((*map)[i]));
			(*map)[i] = tempstr;
		}
		i++;
	}
}

static int	wall_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1')
			return (0);
		i++;
	}
	i = -1;
	while (map[++i])
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			return (0);
	i--;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

static t_error_type	is_map_valid(char **map)
{
	if (!wall_check(map))
		return (WALL_ERROR);
	if (!player_check(map))
		return (PLAYER_ERROR);
	return (CHECK_OK);
}

t_error_type	parse_map(int fd, int lines_num, char ***map)
{
	char	*temp;
	int		i;

	i = 0;
	*map = malloc(sizeof(char *) * (lines_num + 1));
	temp = get_next_line(fd, 0);
	while (temp)
	{
		if (temp[0])
			(*map)[i++] = ft_strcpy(temp);
		free(temp);
		temp = get_next_line(fd, 0);
	}
	(*map)[i] = NULL;
	(*map) = ft_replace_spaces_with_1((*map));
	return (is_map_valid(*map));
}
