/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 17:08:07 by vvermot-          #+#    #+#             */
/*   Updated: 2022/03/11 14:14:26 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_freejoin(char *s1, char *s2)
{
	char				*newstr;
	int					newstrsz;
	unsigned int		i;
	unsigned int		j;

	if (!s1 || !s2)
		return (0);
	j = 0;
	newstrsz = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = malloc (sizeof(char) * newstrsz);
	if (newstr == 0)
		return (0);
	i = ft_strlcpy(newstr, s1, newstrsz);
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	free(s1);
	return (newstr);
}

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
		*line = ft_substr(*buf_pos, 0, i);
		i++;
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

char	*get_next_line(int fd, int new_call)
{
	char static	*buf_pos = NULL;
	char		*buffer;
	char		*line;
	static int	is_empty = 0;
	int			file;

	file = 1;
	if (new_call)
		buf_pos = NULL;
	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer || !check_validity(fd, &buffer, &is_empty))
		return (NULL);
	if (!buf_pos && file)
		buf_pos = ft_strdup("");
	while (file && !ft_strchr(buf_pos, '\n'))
	{
		file = read(fd, buffer, BUFFER_SIZE);
		buffer[file] = '\0';
		buf_pos = ft_freejoin(buf_pos, buffer);
		is_empty++;
	}
	buf_pos = copy_line(&line, &buf_pos, &is_empty);
	free(buffer);
	buffer = NULL;
	return (line);
}
