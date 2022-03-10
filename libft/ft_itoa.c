/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 01:40:57 by qbrechbu          #+#    #+#             */
/*   Updated: 2021/10/19 04:06:37 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (nbr * -1);
	else if (nbr > 0)
		return (nbr);
	return (0);
}

static void	ft_strrev(char *str)
{
	size_t	length;
	size_t	i;
	char	tp;

	length = ft_strlen(str);
	i = 0;
	while (i < length / 2)
	{
		tp = str[i];
		str[i] = str[length - i - 1];
		str[length - i - 1] = tp;
		i++;
	}
}

static int	szmalloc(int nbr)
{
	int	neg;
	int	count;

	neg = (nbr < 0);
	count = 1;
	if (neg)
		nbr *= -1;
	while (nbr / 10 > 0)
	{
		nbr /= 10;
		count++;
	}
	return (count + neg + 1);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				neg;
	unsigned int	sz;

	neg = (n < 0);
	str = ft_calloc(szmalloc(n), sizeof(char));
	if (!str)
		return (0);
	if (n == 0)
		str[0] = '0';
	sz = 0;
	while (n != 0)
	{
		str[sz++] = '0' + ft_abs(n % 10);
		n = (n / 10);
	}
	if (neg)
		str[sz] = '-';
	ft_strrev(str);
	return (str);
}
