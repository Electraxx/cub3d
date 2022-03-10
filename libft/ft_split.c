/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 01:55:14 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/01/24 11:35:31 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	finalsz(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*s)
	{
		if (i == 0 && *s != c)
		{
			i = 1;
			count++;
		}
		else if (i == 1 && *s == c)
			i = 0;
		s++;
	}
	return (count);
}

static int	substrsz(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}

static void	*freearr(char **arr, int i)
{
	while (i-- > 0)
	{
		free(arr[i]);
	}
	free(arr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		arrsz;
	int		i;

	i = 0;
	if (!s)
		return (0);
	arrsz = finalsz((char *)s, c);
	result = malloc((arrsz + 1) * sizeof(char *));
	if (!result)
		return (0);
	while (arrsz--)
	{
		while (*s == c && *s != '\0')
			s++;
		result[i] = ft_substr((char *)s, 0, substrsz((char *)s, c));
		if (!result[i])
			return (freearr(result, i));
		s += substrsz((char *)s, c);
		i++;
	}
	result[i] = 0;
	return (result);
}
