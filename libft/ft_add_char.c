/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 16:48:41 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/16 16:11:16 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//frees the old str and replace it with a new str with an added char
int	ft_add_char(char **str, char added_char)
{
	char			*temp;
	unsigned int	i;
	unsigned int	sz_malloc;

	if (!str)
		return (0);
	sz_malloc = ft_strlen(*str) + 2;
	temp = malloc(sizeof(char) * sz_malloc);
	if (sz_malloc <= 0)
		return (1);
	i = 0;
	while (i < sz_malloc - 2)
	{
		temp[i] = str[0][i];
		i++;
	}
	temp[i] = added_char;
	i++;
	temp[i] = 0;
	*str = temp;
	return (1);
}
