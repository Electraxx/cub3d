/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copy_2d_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:35:30 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/17 17:01:20 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_copy_2d_str(char **ori)
{
	char	**cpy;
	int		i;

	i = 0;
	cpy = malloc(sizeof(char *) * (ft_2dim_char_sz(ori) + 1));
	cpy[ft_2dim_char_sz(ori)] = NULL;
	while (ori[i])
	{
		cpy[i] = ft_strcpy((const char *)ori[i]);
		i++;
	}
	return (cpy);
}
