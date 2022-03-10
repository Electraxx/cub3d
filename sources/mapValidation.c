/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapValidation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:08:23 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/03/10 10:31:52 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

char	**map_to_str2(char *path)
{
	int		fd;
	char	*buff;
	char	*str;
	char	**res;

	fd = open(path, O_RDONLY);
	//if (fd < 0) //TODO ADD invalid map;
	//	invalid_map();
	buff = ft_calloc(10000, sizeof(char));
	str = ft_calloc(10000, sizeof(char));
	while (read(fd, buff, 10000))
		str = ft_strjoin(str, buff);
	free (buff);
	res = ft_split(str, '\n');
	free (str);
	return (res);
}

int	wall_check(char **map)
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

int	sz_check(char **map)
{
	unsigned int	flen;
	int				i;

	i = 0;
	flen = ft_strlen(map[0]);
	while (map[i])
	{
		if (ft_strlen(map[i]) != flen)
			return (0);
		i++;
	}
	return (1);
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

int	is_map_valid(char **map)
{
	if (sz_check(map) && wall_check(map) && chars_check(map))
		return (1);
	return (0);
}
