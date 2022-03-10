/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_index.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:28:20 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/16 11:08:20 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_get_env_index(char **env, char *key)
{
	char	*tempkey;
	int		sz;
	int		i;
	int		eq_loc;

	i = 0;
	sz = 0;
	eq_loc = 0;
	while (env[i])
	{
		tempkey = ft_substr(env[i], 0, ft_strlen(key));
		sz = ft_strlen(tempkey);
		if (ft_strncmp(key, tempkey, ft_strlen(key)) == 0 && env[i][sz] == '=')
		{
			eq_loc = ft_str_contains(env[i], "=");
			free(tempkey);
			return (i);
		}
		free(tempkey);
		i++;
	}
	return (-1);
}
