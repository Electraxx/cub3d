/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_contains.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvermot- <vvermot-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 22:11:06 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/02/15 15:49:50 by vvermot-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//returns the index or -1 if there is no chars
int	ft_str_contains(char *str, char *set)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == str[i])
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}
