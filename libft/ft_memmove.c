/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 01:44:32 by qbrechbu          #+#    #+#             */
/*   Updated: 2021/10/19 01:45:25 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*csrc;
	unsigned char		*cdest;
	unsigned int		i;

	csrc = (unsigned char *)src;
	cdest = (unsigned char *)dst;
	if ((!cdest && !csrc) || len <= 0)
		return (dst);
	i = 0;
	if (csrc < cdest)
		while (++i <= len)
			cdest[len - i] = csrc[len - i];
	else
		while (len-- > 0)
			*(cdest++) = *(csrc++);
	return (dst);
}
