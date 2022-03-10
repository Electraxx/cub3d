/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pow.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 16:55:12 by qbrechbu          #+#    #+#             */
/*   Updated: 2021/12/07 12:27:41 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	poww(int nbr, int pow)
{
	int	cpy;

	cpy = nbr;
	if (pow == 0 || pow < 0)
		return (1);
	while (pow != 1)
	{
		nbr *= cpy;
		pow--;
	}
	return (nbr);
}
