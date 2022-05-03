/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:02:48 by vvermot-          #+#    #+#             */
/*   Updated: 2022/05/03 16:06:40 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cub3d.h"

void	print_error_exit(t_error_type error)
{
	if (error == MAP_ERROR)
		printf("Map error\n");
	else if (error == TEXTURE_ERROR)
		printf("Texture error\n");
	else if (error == COLOR_ERROR)
		printf("Color error\n");
	else if (error == MISSING_TEXTURE)
		printf("Missing texture error (verify the path)\n");
	else if (error == MISSING_CARDINAL)
		printf("Missing cardinal error\n");
	else if (error == PLAYER_ERROR)
		printf("There should be ONE player on the map\n");
	else if (error == WALL_ERROR)
		printf("The map should be surrounded by walls\n");
	else if (error == FORMAT_ERROR)
		printf("The format of the first lines is not correct\n");
	exit(0);
}
