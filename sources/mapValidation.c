/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapValidation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:08:23 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/03/10 15:09:07 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

int		ft_check_extension(char *path)
{
	int	i;

	i = ft_strlen(path);
	path += (i - 4);
	if (!ft_same_str(path, ".cub"))
		return (0);
	return (1);
}

char	**ft_replace_spaces_with_1(char **map)
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

int	wall_check(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' && map[0][i] != '\n')
			return (0);
		i++;
	}
	i = -1;
	while (map[++i])
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 2] != '1')
			return (0);
	i--;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != '1' && map[i][j] != '\n')
			return (0);
		j++;
	}
	return (1);
}

error_type	is_map_valid(char **map)
{
	if (wall_check(map))
		return (CHECK_OK);
	return (MAP_ERROR);
}

int		get_number_of_lines(int fd)
{
	char	*temp;
	int		ret;

	temp = get_next_line(fd);
	ret = 0;
	while (temp)
	{
		if (temp[0] != '\n')
			ret++;
		free(temp);
		temp = get_next_line(fd);
	}
	if (ret - 6 <= 0)
		return (0);
	else
		return (ret - 6);
}

char **parse_map(int fd, int lines_num)
{
	char **map;
	char *temp;
	int	 i;

	i = 0;
	map = malloc(sizeof(char *) * lines_num + 1);
	temp = get_next_line(fd);
	while (temp)
	{
		if (temp[0] != '\n')
			map[i++] = ft_strcpy(temp);
		free(temp);
		temp = get_next_line(fd);
	}
	map[i] = NULL;
	map = ft_replace_spaces_with_1(map);
	if (!is_map_valid(map))
	{
		printf("The map is not valid");
		return (NULL);
	}
	return (map);
}

char	**ft_parse_first_6_lines(char *path)
{
	int		fd;
	char	**res;
	char	*temp;
	int		valid_line_count;
	int 	lines_number;

	valid_line_count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0 || !ft_check_extension(path))
		return (NULL);
	lines_number = get_number_of_lines(fd);
	close(fd);
	fd = open(path, O_RDONLY);
	if (fd < 0 || !ft_check_extension(path))
		return (NULL);
	temp = get_next_line(fd);
	while (temp && valid_line_count < 6)
	{
		if (temp[0] == '\n')
		{
			free(temp);
			temp = get_next_line(fd);
			continue ;
		}
		else if ((temp[0] == 'F' || temp[0] == 'C') && temp[1] == ' ')
		{
			valid_line_count++;
			// printf("Send it to color check");
		}
		else
		{
			valid_line_count++;
			// printf("Send it to texture check");
		}
		free(temp);
		temp = get_next_line(fd);
	}
	res = parse_map(fd, lines_number);
	return (res);
}

int	chars_check(char **map)
{
	char	*cnt;
	int		i;
	int		j;

	i = 0;
	cnt = ft_calloc(257, sizeof(int));
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			cnt[(int)map[i][j]]++;
			j++;
		}
		i++;
	}
	if (cnt['C'] > 0 && cnt['E'] > 0 && cnt['P'] == 1)
	{
		free (cnt);
		return (1);
	}
	free (cnt);
	return (0);
}

