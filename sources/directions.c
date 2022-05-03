/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:02:29 by vvermot-          #+#    #+#             */
/*   Updated: 2022/05/03 16:02:33 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

char	get_adjacent_cardinal(int vec, char curr)
{
	char	*cardinal;
	int		i;
	char	ret;

	i = 0;
	cardinal = ft_strcpy("NESW");
	while (curr != cardinal[i])
		i++;
	i += vec;
	ret = cardinal[i % 4];
	free(cardinal);
	return (ret);
}

void	set_player_dir(t_camera *camera, char goal)
{
	double	old_dirx;
	double	old_planex;
	char	curr;
	int		i;
	double	rad;

	curr = 'W';
	i = 0;
	while (curr != goal)
	{
		curr = get_adjacent_cardinal(1, curr);
		i++;
	}
	old_planex = camera->planeX;
	old_dirx = camera->dirX;
	rad = (i * -90) * (PI / 180);
	camera->dirX = old_dirx * cos(rad) - camera->dirY * sin(rad);
	camera->dirY = old_dirx * sin(rad) + camera->dirY * cos(rad);
	camera->planeX = camera->planeX * cos(rad) - camera->planeY * sin(rad);
	camera->planeY = old_planex * sin(rad) + camera->planeY * cos(rad);
}

void	get_player_orientation(char **map, t_config *cfg)
{
	int		i;
	int		j;
	char	*cardi;
	char	*tmp;

	i = 0;
	cardi = ft_strcpy("NESW");
	while (map[i])
	{
		j = 0;
		while (cardi[j])
		{
			tmp = ft_strchr(map[i], cardi[j]);
			if (tmp != NULL)
			{
				cfg->firstDir = tmp[0];
				free(cardi);
				return ;
			}
			j++;
		}
		i++;
	}
	free(cardi);
}
