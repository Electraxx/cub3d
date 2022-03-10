/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pushfreestr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 16:38:27 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/16 11:06:54 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pushfreestr(char **str, char *freestr)
{
	char	*tmp;
	int		oldsz;

	tmp = *str;
	oldsz = ft_strlen(*str);
	*str = ft_strjoin(*str, freestr);
	free(tmp);
	free(freestr);
	return (ft_strlen(*str) - oldsz);
}
