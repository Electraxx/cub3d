/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:22:17 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/16 11:06:21 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_set_env(char **env, char *key, char *value)
{
	int		index;
	char	*temp;
	char	*until_eq;
	char	*valcpy;

	if (!env || !key || !value)
		return ;
	index = ft_get_env_index(env, key);
	if (index == -1)
		return ;
	temp = env[index];
	until_eq = ft_substr(temp, 0, ft_str_contains(temp, "=") + 1);
	valcpy = ft_strcpy(value);
	env[index] = ft_strjoin(until_eq, valcpy);
	free(until_eq);
	free(valcpy);
}
