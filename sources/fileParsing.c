#include "../headers/cub3d.h"

static int	get_number_of_lines(int fd)
{
	char	*temp;
	int		ret;

	temp = get_next_line(fd, 0);
	ret = 0;
	while (temp)
	{
		if (temp[0] != '\n')
			ret++;
		free(temp);
		temp = get_next_line(fd, 0);
	}
	if (ret - 6 <= 0)
		return (0);
	else
		return (ret - 6);
}

static int	ft_check_extension(char *path)
{
	int	i;

	i = ft_strlen(path);
	path += (i - 4);
	if (!ft_same_str(path, ".cub"))
		return (0);
	return (1);
}

int	ft_parse_file(char *path, t_cardi_check *cardiCheck)
{
	int		fd;
	int		ret;
	char	**map;
	int		lines_number;

	fd = open(path, O_RDONLY);
	if (fd < 0 || !ft_check_extension(path))
		return (MAP_ERROR);
	lines_number = get_number_of_lines(fd);
	close(fd);
	fd = open(path, O_RDONLY);
	if (fd < 0 || !ft_check_extension(path))
		return (MAP_ERROR);
	ret = ft_parse_first_6_lines(fd, cardiCheck);
	if (ret < 0)
		print_error_exit(ret);
	ret = parse_map(fd, lines_number, &map);
	if (ret < 0)
		print_error_exit(ret);
	return (CHECK_OK);
}

error_type	ft_parse_first_6_lines(int fd, t_cardi_check *cardiCheck)
{
	char	*temp;
	int		valid_line_count;

	temp = get_next_line(fd, 1);
	valid_line_count = 0;
	while (temp)
	{
		if (temp[0] == '\n')
		{
			free(temp);
			temp = get_next_line(fd, 0);
			continue ;
		}
		else if ((temp[0] == 'F' || temp[0] == 'C') && temp[1] == ' ')
		{
			if (is_color_valid(temp) < 0)
				return (is_color_valid(temp));
		}
		else if (is_valid_cardinal(ft_substr(temp, 0, 2)))
		{
			if (texture_check(temp, cardiCheck) < 0)
				return (texture_check(temp, cardiCheck));
		}
		else
			break ;
		valid_line_count++;
		free(temp);
		temp = get_next_line(fd, 0);
	}
	if (valid_line_count != 6)
		return (MAP_ERROR);
	return (CHECK_OK);
}
