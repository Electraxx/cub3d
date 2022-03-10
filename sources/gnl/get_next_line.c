/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:08:07 by vvermot-          #+#    #+#             */
/*   Updated: 2021/10/28 14:02:39 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*copy_line(char **line, char **buf_pos, int *is_empty)
{
	int			i;
	char		*new_pos;

	new_pos = NULL;
	i = 0;
	while ((*buf_pos)[i] != '\n' && (*buf_pos)[i])
		i++;
	if ((*buf_pos)[i] == '\n')
	{
		i++;
		*line = ft_substr(*buf_pos, 0, i);
		*is_empty = *is_empty + 1;
	}
	else if ((*buf_pos)[i] == '\0' && *buf_pos)
		*line = ft_strdup(*buf_pos);
	new_pos = ft_strdup(&(*buf_pos)[i]);
	free(*buf_pos);
	*buf_pos = NULL;
	if (i == 0)
	{
		free(new_pos);
		free(*line);
		*line = NULL;
	}
	return (new_pos);
}

int	check_validity(int fd, char **buffer, int *is_empty)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (0);
	}
	if (read(fd, *buffer, 0) < 0 || *is_empty == 1)
	{
		*is_empty = 0;
		free(*buffer);
		*buffer = NULL;
		return (0);
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char static	*buf_pos = NULL;
	char		*buffer;
	char		*line;
	static int	is_empty = 0;
	static int	file = 1;

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (!check_validity(fd, &buffer, &is_empty))
		return (NULL);
	if (!buf_pos && file)
		buf_pos = ft_strdup("");
	while (file && !ft_strchr(buf_pos, '\n'))
	{
		file = read(fd, buffer, BUFFER_SIZE);
		buffer[file] = '\0';
		buf_pos = ft_strjoin(buf_pos, buffer);
		is_empty++;
	}
	buf_pos = copy_line(&line, &buf_pos, &is_empty);
	free(buffer);
	buffer = NULL;
	return (line);
}
