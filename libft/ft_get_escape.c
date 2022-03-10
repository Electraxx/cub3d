/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_escape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 17:03:48 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/16 11:08:34 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	ft_get_escape(char c)
{
	if (c == 'a')
		return ('\a');
	if (c == 'b')
		return ('\b');
	if (c == 'e')
		return ('\e');
	if (c == 'f')
		return ('\f');
	if (c == 'n')
		return ('\n');
	if (c == 'r')
		return ('\r');
	if (c == 't')
		return ('\t');
	if (c == 'v')
		return ('\v');
	return (-1);
}
