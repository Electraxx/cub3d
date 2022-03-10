#include "../headers/cub3d.h"

error_type is_color_valid(char *color_line)
{
	char	*color;
	char	**c_strs;
	int		*colors;
	int		i;

	i = 0;
	color = color_line + 2;
	c_strs = ft_split(color, ',');
	if (ft_2dim_char_sz(c_strs) != 3)
	{
		ft_free_2d_str(c_strs);
		return (COLOR_ERROR);
	}
	colors = malloc(sizeof(int) * 3);
	while (i < 3)
	{
		colors[i] = ft_atoi(c_strs[i]);
		if ((colors[i] > 255 || colors[i] < 0) && ft_is_str_full_num(c_strs[i]))
		{
			free(colors);
			ft_free_2d_str(c_strs);
			return (COLOR_ERROR);
		}
		i++;
	}
	free(colors);
	ft_free_2d_str(c_strs);
	return (CHECK_OK);
}