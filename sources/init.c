#include "../headers/cub3d.h"

void	init_cardi_struct(t_cardi_check *cardi)
{
	cardi->val = malloc(sizeof(int) * 4);
	cardi->val[0] = 0;
	cardi->val[1] = 0;
	cardi->val[2] = 0;
	cardi->val[3] = 0;
	cardi->cardi = malloc(sizeof(char *) * 4);
	cardi->cardi[0] = ft_strcpy("NO");
	cardi->cardi[1] = ft_strcpy("SO");
	cardi->cardi[2] = ft_strcpy("WE");
	cardi->cardi[3] = ft_strcpy("EA");
}
