/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 01:00:24 by qbrechbu          #+#    #+#             */
/*   Updated: 2021/10/19 02:18:43 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ischarinset(char c, const char *set)
{
	while (*set != '\0')
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned int	i;
	unsigned int	start;
	unsigned int	end;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && ft_ischarinset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_ischarinset(s1[end - 1], set))
		end--;
	str = (char *)malloc (sizeof(*s1) * (end - start + 1));
	if (!str)
		return (0);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}
