/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_double_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 16:55:32 by vvermot-          #+#    #+#             */
/*   Updated: 2022/03/10 10:34:54 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_double_quote(char const *s, int j, char c)
{
	int	i;

	i = 2;
	if (c == '"')
	{
		while (s[++j])
		{
			if (s[j] == '"')
				return (i);
			i++;
		}
	}
	else if (c == '\'')
	{
		while (s[++j])
		{
			if (s[j] == '\'')
				return (i);
			i++;
		}
	}
	return (0);
}
