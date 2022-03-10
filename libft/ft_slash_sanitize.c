/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_slash_sanitize.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:25:08 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/16 11:05:50 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_2d_slash_sanitize(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i])
	{
		ft_slash_sanitize(&str[i]);
		i++;
	}
}

void	ft_slash_sanitize(char **str)
{
	size_t	i;
	char	*strc;

	strc = *str;
	i = 0;
	while (strc[i])
	{
		if (strc[i] == '\\')
		{
			ft_remove_char(str, i);
			i++;
		}
		i++;
	}
}
