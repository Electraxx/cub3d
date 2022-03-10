/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:54:37 by qbrechbu          #+#    #+#             */
/*   Updated: 2021/10/19 01:42:55 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*dest;
	unsigned char	*s;

	s = (unsigned char *)src;
	dest = (unsigned char *)dst;
	i = 0;
	while (n > i)
	{
		dest[i] = s[i];
		if (dest[i] == (unsigned char)c)
			return ((void *) dest + i + 1);
		i++;
	}
	return (0);
}
