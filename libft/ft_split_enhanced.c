/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_enhanced.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 01:55:14 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/16 10:56:35 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	finalsz(char *s, t_split counts, int j)
{
	while (s[++j])
	{
		counts.count += inc_count((char *)s, &j, &counts);
		if (s[j] == '|' || (s[j] == '>' && s[j + 1] != '>')
			|| (s[j] == '<' && s[j + 1] != '<'))
			counts.count++;
		if ((s[j] == '<' && s[j + 1] == '<')
			|| (s[j] == '>' && s[j + 1] == '>'))
		{
			j += 2;
			counts.count++;
		}
	}
	return (counts.count);
}

static int	substrsz(char **s, char c, int *is_sep)
{
	int	i;

	i = 0;
	while ((*s)[i] && (*s)[i] != c)
	{
		if ((*s)[i] == '"' || (*s)[i] == '\'')
		{
			if (get_quote_ret(i, s))
				return (get_quote_ret(i, s));
		}
		if (((*s)[i] == '>' && (*s)[i + 1] == '>')
			|| ((*s)[i] == '<' && (*s)[i + 1] == '<'))
		{
			*is_sep = 2;
			break ;
		}
		else if (((*s)[i] == '|' || (*s)[i] == '>' || (*s)[i] == '<'))
		{
			*is_sep = 1;
			break ;
		}
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

static int	get_results(char **s, int *i, char ***result)
{
	int	size;
	int	is_sep;

	is_sep = 0;
	size = substrsz(s, ' ', &is_sep);
	if (size)
	{
		(*result)[*i] = ft_substr((char *)(*s), 0, size);
		if (!(*result)[(*i)])
			return (0);
	}
	(*s) += size;
	if (is_sep && !size)
	{
		(*result)[(*i)++] = ft_substr((char *)(*s), 0, is_sep);
		if (!(*result)[(*i - 1)])
			return (0);
		(*s) += is_sep;
		is_sep = 0;
	}
	else
		(*i)++;
	return (1);
}

char	**ft_split_enhanced(char *s, char c)
{
	char	**result;
	int		arrsz;
	int		i;
	t_split	trash;

	(void)c;
	i = 0;
	trash.i = 0;
	trash.count = 0;
	if (!s)
		return (0);
	arrsz = finalsz((char *)s, trash, -1);
	result = malloc((arrsz + 1) * sizeof(char *));
	if (!result)
		return (0);
	while (arrsz-- && *s)
	{
		while (ft_whitespace(*s) && *s != '\0')
			s++;
		if (!get_results(&s, &i, &result))
			return (freearr(result, i));
	}
	result[i] = NULL;
	return (result);
}
