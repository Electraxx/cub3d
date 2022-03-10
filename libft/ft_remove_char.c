/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:55:17 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/07 16:17:14 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_remove_char(char **str, unsigned int index)
{
	size_t	len;
	size_t	i;
	char	*newstr;
	char	*strp;

	strp = *str;
	len = ft_strlen(strp);
	i = 0;
	if (index > len - 2)
		return ;
	newstr = ft_calloc(len, sizeof(char));
	while (i < index)
	{
		newstr[i] = strp[i];
		i++;
	}
	i++;
	while (strp[i])
	{
		newstr[i - 1] = strp[i];
		i++;
	}
	*str = newstr;
}
