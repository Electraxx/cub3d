/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 10:25:12 by vvermot-          #+#    #+#             */
/*   Updated: 2022/02/14 10:25:24 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_args(char **args, char *new)
{
	int		i;
	int		count;
	char	**ret;

	count = 0;
	i = -1;
	while (args[++i])
		;
	ret = malloc(sizeof(char *) * (i + 2));
	i = -1;
	while (args[++i])
		ret[i] = ft_strcpy(args[i]);
	ret[i] = ft_strcpy(new);
	ret[++i] = NULL;
	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
	return (ret);
}
