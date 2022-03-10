/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_numsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 21:27:54 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/01/10 16:18:06 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_numsize(int n)
{
	int	sz;

	sz = 1;
	while (n / 10)
	{
		sz++;
		n /= 10;
	}
	return (sz);
}
