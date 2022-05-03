/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bchar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:10:33 by vvermot-          #+#    #+#             */
/*   Updated: 2022/05/03 16:10:37 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bchar(void *s, size_t n, char c)
{
	unsigned char	*ptr;
	unsigned int	i;

	i = 0;
	ptr = s;
	while (n > i)
	{
		ptr[i] = c;
		i++;
	}
}
