/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:54:37 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/01/10 13:53:11 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	incrvar(int *v1, int *v2)
{
	*v1 = *v1 + 1;
	*v2 = *v2 + 1;
}

static int	retval(int len, int neg, int num)
{
	if (len > 10 && neg == 1)
		return (-1);
	else if (len > 10)
		return (0);
	return (num * neg);
}

int	ft_atoi(const char *str)
{
	int	neg;
	int	num;
	int	i;
	int	len;

	i = 0;
	neg = 1;
	num = 0;
	len = 0;
	while (ft_whitespace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		incrvar(&i, &len);
	}
	return (retval(len, neg, num));
}

//renvoie le chiffre ou -1 si trop grand (ne filtre pas les négatifs)
int	ft_atoi_check_size(char *str)
{
	int	or_sz;
	int	sz_atoi;
	int	atoi;

	or_sz = ft_strlen(str);
	atoi = ft_atoi(str);
	sz_atoi = ft_numsize(atoi);
	if (or_sz == sz_atoi)
		return (atoi);
	return (-1);
}
