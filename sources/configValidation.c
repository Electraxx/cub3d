#include "../headers/cub3d.h"

error_type check_all_cardi(t_cardi_check *cardi)
{
	int	i = 0;

	while (i < 4)
	{
		if (!cardi->val[i])
			return (MISSING_CARDINAL);
		i++;
	}
	return (CHECK_OK);
}