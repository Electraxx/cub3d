/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_2d_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:20:03 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/17 17:00:56 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_2d_str(char **strs, int fd, char	*prompt)
{
	size_t	i;

	i = 0;
	while (strs[i])
	{
		ft_putstr_fd(prompt, fd);
		ft_putstr_fd(strs[i], fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
}
