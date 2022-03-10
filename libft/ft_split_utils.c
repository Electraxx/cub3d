/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 19:01:18 by vvermot-          #+#    #+#             */
/*   Updated: 2022/02/16 11:23:12 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	update_count(t_split *counts, int opt, int *count)
{
	if (opt == 0)
	{
		counts->i = 0;
		(*count)++;
	}
	else if (opt == 1)
	{
		counts->i = 1;
		(*count)++;
	}
}

int	inc_count(char *s, int *j, t_split *counts)
{
	int	count;
	int	old_j;

	old_j = 0;
	count = 0;
	if (s[*j] == '"' || s[*j] == '\'')
	{
		old_j = *j;
		*j += is_double_quote(s, *j, s[*j]);
		if (*j != old_j || counts->i == 0)
			update_count(counts, 0, &count);
	}
	else if (counts->i == 0)
		update_count(counts, 1, &count);
	else if (counts->i == 1 && (s[*j] == ' ' || s[*j] == '|' || (s[*j] == '<'
				&& s[(*j) + 1] != '<') || (s[*j] == '>'
				&& s[(*j) + 1] != '>')
			|| (s[(*j)] == '<' && s[(*j) + 1] == '<') || (s[*j] == '>'
				&& s[(*j) + 1] == '>')))
		counts->i = 0;
	return (count);
}

int	get_quote_ret(int i, char **s)
{
	int	ret;

	ret = 0;
	if (is_double_quote(*s, i, (*s)[i]))
	{
		ret = is_double_quote(*s, i, (*s)[i]);
		return (ret - i);
	}
	return (0);
}
