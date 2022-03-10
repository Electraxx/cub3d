/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 01:55:28 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/17 13:49:00 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*t;
	unsigned int	i;
	unsigned int	maxi;

	maxi = ft_strlen(s) + 1;
	i = 0;
	while (i < maxi)
	{
		if ((char) c == s[i])
		{
			t = (char *)&s[i];
			return (t);
		}
		i++;
	}
	return (0);
}
