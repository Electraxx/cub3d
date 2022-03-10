/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:13:36 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/01/10 16:17:37 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(const char *src)
{
	int		length;
	char	*cpy;

	length = ft_strlen(src);
	cpy = malloc(sizeof(char) * length + 1);
	ft_memcpy(cpy, src, length);
	cpy[length] = 0;
	return (cpy);
}
