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

static int	player_check(char **map)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				player_count++;
			j++;
		}
		i++;
	}
	if (player_count == 1)
		return (1);
	return (0);
}

static error_type	is_map_valid(char **map)
{
	if (!wall_check(map))
		return (WALL_ERROR);
	if (!player_check(map))
		return (PLAYER_ERROR);
	return (CHECK_OK);
}

error_type	parse_map(int fd, int lines_num, char ***map)
{
	char *temp;
	int	 i;

	i = 0;
	*map = malloc(sizeof(char *) * (lines_num + 1));
	temp = get_next_line(fd, 0);
	while (temp)
	{
		if (temp[0] != '\n')
			(*map)[i++] = ft_strcpy(temp);
		free(temp);
		temp = get_next_line(fd, 0);
	}
	(*map)[i] = NULL;
	(*map) = ft_replace_spaces_with_1((*map));
	return (is_map_valid(*map));
}
