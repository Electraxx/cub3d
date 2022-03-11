#include "../headers/cub3d.h"
int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	t_cardi_check cardiCheck;
	init_cardi_struct(&cardiCheck);
	ft_parse_file(argv[1], &cardiCheck);
	// //error_type test = is_color_valid("F -1,255,255");
	// error_type test1 = texture_check("NO lol.txt", &cardiCheck);
	// error_type test2 = texture_check("SO lol.txt", &cardiCheck);
	// error_type test3 = texture_check("WE lols.txt", &cardiCheck);
	// error_type test4 = texture_check("EA lol.txt", &cardiCheck);
	// error_type finalTest = check_all_cardi(&cardiCheck);
	// printf ("t1 %d\n", test1);
	// printf ("t2 %d\n", test2);
	// printf ("t3 %d\n", test3);
	// printf ("t4 %d\n", test4);
	// printf ("tf %d\n", finalTest);
	// (void) test1;
	// (void) test2;
	// (void) test3;
	// (void) test4;
}
