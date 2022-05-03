#include "../headers/cub3d.h"

static t_error_type	ft_check_color(int *colors, char **c_strs)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		colors[i] = ft_atoi(c_strs[i]);
		ft_is_str_full_num(c_strs[i]);
		if ((colors[i] > 255 || colors[i] < 0)
			|| !ft_is_str_full_num(c_strs[i]))
			return (COLOR_ERROR);
		i++;
	}
	return (CHECK_OK);
}

t_error_type	is_color_valid(char *color_line)
{
	char	*color;
	char	**c_strs;
	int		*colors;

	color = color_line + 2;
	c_strs = ft_split(color, ',');
	if (ft_2dim_char_sz(c_strs) != 3)
	{
		ft_free_2d_str(c_strs);
		return (COLOR_ERROR);
	}
	colors = malloc(sizeof(int) * 3);
	if (ft_check_color(colors, c_strs) == COLOR_ERROR)
	{
		free(colors);
		ft_free_2d_str(c_strs);
		return (COLOR_ERROR);
	}
	free(colors);
	ft_free_2d_str(c_strs);
	return (CHECK_OK);
}

void	load_color(t_config *cfg, char *color, char type)
{
	char	**bytes;

	bytes = ft_split(color, ',');
	if (type == 'C')
		cfg->ceiling = creatergba(ft_atoi(bytes[0]),
				ft_atoi(bytes[1]), ft_atoi(bytes[2]), 0);
	else if (type == 'F')
		cfg->floor = creatergba(ft_atoi(bytes[0]),
				ft_atoi(bytes[1]), ft_atoi(bytes[2]), 0);
	ft_free_2d_str(bytes);
}
