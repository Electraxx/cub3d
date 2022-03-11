#ifndef CUB3D_H
# define CUB3D_H
# include <libft.h>
# include <get_next_line.h>
# include <fcntl.h>
# include "error.h"
# include "colorValidation.h"
# include <fcntl.h>
# include <stdio.h>

typedef struct s_color{
	int	r;
	int	g;
	int	b;
} t_color;

typedef struct s_config{
	t_color	*floor;
	t_color	*ceiling;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char**map;
} t_config;

typedef struct s_cardi_check{
	int *val;
	char **cardi;
} t_cardi_check;

void		init_cardi_struct(t_cardi_check *cardi);
error_type	texture_check(char *t_path, t_cardi_check *check_cardi);
int			check_all_cardi(t_cardi_check *cardi);

// colorValidations.c
error_type 		is_color_valid(char *color_line);

// mapValidation.c
error_type		ft_parse_first_6_lines(int fd, t_cardi_check *cardiCheck);
error_type		parse_map(int fd, int lines_num, char ***map);

// textureValidation.c
int 			is_valid_cardinal(char *cardinal);

// debug.c
void			ft_print_map(char **map);

// fileParsing.c
error_type		ft_parse_file(char *path, t_cardi_check *cardiCheck);

// error.c
void			print_error_exit(error_type error);

#endif
