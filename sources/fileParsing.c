/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fileParsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:03:45 by vvermot-          #+#    #+#             */
/*   Updated: 2022/05/03 16:03:52 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

static int	get_number_of_lines(int fd)
{
	char	*temp;
	int		ret;

	temp = get_next_line(fd, 0);
	ret = 0;
	while (temp)
	{
		if (temp[0])
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
	size_t	i;

	i = ft_strlen(path);
	path += (i - 4);
	if (!ft_same_str(path, ".cub"))
		return (0);
	return (1);
}

t_error_type	ft_check_line(char *temp, t_cardi_check *cardiCheck,
	t_config *cfg, int *cnt)
{
	if ((temp[0] == 'F' || temp[0] == 'C'))
	{
		if (is_color_valid(temp) < 0)
			return (is_color_valid(temp));
		load_color(cfg, temp + 2, temp[0]);
		(*cnt)++;
		return (CHECK_OK);
	}
	else if (is_valid_cardinal(ft_substr(temp, 0, 2)))
	{
		if (texture_check(temp, cardiCheck) < 0)
			return (texture_check(temp, cardiCheck));
		load_texture(cfg, temp + 3, temp[0]);
		(*cnt)++;
		return (CHECK_OK);
	}
	return (FORMAT_ERROR);
}

t_error_type	ft_check_lines(t_cardi_check *cardiCheck,
		t_config *cfg, int fd)
{
	int				count;
	t_error_type	type;
	char			*temp;

	temp = get_next_line(fd, 1);
	count = 0;
	while (temp && count < 6)
	{
		type = ft_check_line(temp, cardiCheck, cfg, &count);
		if (!temp[0])
		{
			free(temp);
			temp = get_next_line(fd, 0);
			continue ;
		}
		else if (type != CHECK_OK)
		{
			free(temp);
			return (type);
		}
		free(temp);
		temp = get_next_line(fd, 0);
	}
	free(temp);
	return (CHECK_OK);
}

t_error_type ft_parse_file(char *path, t_cardi_check *cardiCheck, t_game *game)
{
	int				fd;
	t_error_type	ret;
	char			**map;
	int				lines_number;

	fd = open(path, O_RDONLY);
	if (fd < 0 || !ft_check_extension(path))
		return (MAP_ERROR);
	lines_number = get_number_of_lines(fd);
	close(fd);
	fd = open(path, O_RDONLY);
	if (fd < 0 || !ft_check_extension(path))
		return (MAP_ERROR);
	init_config_struct(&game->config);
	ret = ft_check_lines(cardiCheck, &game->config, fd);
	if (ret < 0)
		return (ret);
	ret = parse_map(fd, lines_number, &map);
	game->map = map;
	if (ret < 0)
	{
		print_error(ret);
		clean(game);
		exit(0);
	}
	return (CHECK_OK);
}
