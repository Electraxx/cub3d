/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_only_whitespace.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:16:11 by vvermot-          #+#    #+#             */
/*   Updated: 2022/02/17 17:17:06 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_only_whitespace(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_whitespace(str[i]))
			return (0);
	}
	return (1);
}
