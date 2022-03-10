/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 14:39:49 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/16 11:09:07 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

char	*ft_get_env(char **env, char *key)
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
			return (ft_substr(env[i], eq_loc + 1, ft_strlen(env[i])));
		}
		free(tempkey);
		i++;
	}
	return (0);
}
