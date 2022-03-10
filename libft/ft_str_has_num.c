/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_has_num.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 23:39:31 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/15 15:49:41 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_has_num(char *str)
{
	while (*(str++))
		if (ft_isdigit((int) *(str - 1)))
			return (1);
	return (0);
}
