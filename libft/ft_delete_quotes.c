/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 16:33:39 by vvermot-          #+#    #+#             */
/*   Updated: 2022/02/12 16:35:36 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_delete_quotes(char **words)
{
	char	quote;

	quote = (*words)[0];
	if ((quote == '"' || quote == '\'') && is_double_quote((*words), 0, quote))
	{
		(*words) = ft_strtrim(*words, &quote);
	}
}
