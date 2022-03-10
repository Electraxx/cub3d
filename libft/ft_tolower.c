/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 02:11:16 by qbrechbu          #+#    #+#             */
/*   Updated: 2021/10/19 02:11:41 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (ft_isalpha(c))
	{
		if (c >= 65 && c <= 90)
			return (c + 32);
	}
	return (c);
}
