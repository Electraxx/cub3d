#include "libft.h"

void	ft_bchar(void *s, size_t n, char c)
{
	unsigned char	*ptr;
	unsigned int	i;

	i = 0;
	ptr = s;
	while (n > i)
	{
		ptr[i] = c;
		i++;
	}
}