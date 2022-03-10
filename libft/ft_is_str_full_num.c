#include "libft.h"

int ft_is_str_full_num(char *str)
{
	int	i;

	i = 0;
	if(str[0] == '-')
	{
		if(ft_strlen(str) < 2)
			return (0);
		else
			i++;
	}
	while(str[i])
	{
		if(!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
