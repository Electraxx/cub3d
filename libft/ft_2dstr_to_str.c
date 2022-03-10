/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2dstr_to_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 01:03:02 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/16 11:11:36 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_2dstr_to_str(char **tab)
{
	int		i;
	char	*temp;
	char	*str;

	if (!tab)
		return (0);
	i = 1;
	str = ft_strcpy(tab[0]);
	while (tab[i])
	{
		temp = str;
		str = ft_strjoin(str, tab[i]);
		free(temp);
		i++;
	}
	return (str);
}
