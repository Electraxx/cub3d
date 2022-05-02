#include "../headers/cub3d.h"

int	is_valid_cardinal(char *cardinal)
{
	if (ft_strlen(cardinal) != 2)
		return (0);
	if (ft_same_str(cardinal, "NO"))
		return (1);
	if (ft_same_str(cardinal, "WE"))
		return (1);
	if (ft_same_str(cardinal, "EA"))
		return (1);
	if (ft_same_str(cardinal, "SO"))
		return (1);
	return (0);
}

void	set_cardi_values(char *cardi, t_cardi_check *check_cardi)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (ft_same_str(check_cardi->cardi[i], cardi))
			check_cardi->val[i] = 1;
		i++;
	}
}

void	load_texture(t_config *cfg, char *path, char type)
{
	if (type == 'N')
		cfg->path_no = ft_strcpy(path);
	else if (type == 'S')
		cfg->path_so = ft_strcpy(path);
	else if (type == 'E')
		cfg->path_ea = ft_strcpy(path);
	else if (type == 'W')
		cfg->path_we = ft_strcpy(path);
}

error_type	texture_check(char *t_path , t_cardi_check *check_cardi)
{
	char	*substr;

	if (ft_strlen(t_path) < 8)
		return (TEXTURE_ERROR);
	substr = ft_substr(t_path, 0, 2);
	if (open(t_path + 3, O_RDONLY) < 0 || !is_valid_cardinal(substr))
	{
		if (!is_valid_cardinal(substr))
			return (MISSING_CARDINAL);
		free(substr);
		return (TEXTURE_ERROR);
	}
	set_cardi_values(substr, check_cardi);
	free(substr);
	return (CHECK_OK);
}
