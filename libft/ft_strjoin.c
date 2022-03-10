/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 15:49:31 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/01/17 11:17:04 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char				*newstr;
	int					newstrsz;
	unsigned int		i;
	unsigned int		j;

	if (!s1 || !s2)
		return (0);
	j = 0;
	newstrsz = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = malloc (sizeof(char) * newstrsz);
	if (newstr == 0)
		return (0);
	i = ft_strlcpy(newstr, s1, newstrsz);
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		newstr[i] = s2[j];
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}
