/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 01:43:00 by qbrechbu          #+#    #+#             */
/*   Updated: 2021/10/19 01:44:00 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_memchr(const char *s, int c, size_t n)
{
	char			*t;
	unsigned int	i;

	i = 0;
	t = (void *)s;
	while (i < n)
	{
		if ((char) c == t[i])
			return (&t[i]);
		i++;
	}
	return (0);
}
