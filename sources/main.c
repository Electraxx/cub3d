#include "../headers/cub3d.h"
int main()
{
	error_type test = is_color_valid("F a,255,255");
	printf ("%d\n", test);
	(void) test;
}