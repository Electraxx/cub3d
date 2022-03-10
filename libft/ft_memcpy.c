/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 02:12:54 by qbrechbu          #+#    #+#             */
/*   Updated: 2021/10/19 02:13:58 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dest;
	char	*source;

	if (!dst && !src)
		return (0);
	dest = dst;
	source = (char *)src;
	while ((n--) > 0)
		*(dest++) = *(source++);
	return (dst);
}
