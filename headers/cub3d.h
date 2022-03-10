#ifndef CUBE3D_H
# define CUBE3D_H
# include <libft.h>
# include <get_next_line.h>
# include <fcntl.h>

typedef struct s_color{
	int r;
	int g;
	int b;
} t_color;

typedef struct s_config{
	t_color *floor;
	t_color *ceiling;
	char 	*path_no;
	char 	*path_so;
	char 	*path_we;
	char 	*path_ea;
	char 	**map;
} t_config;

int		ft_check_extension(char *path);
char	**ft_parse_first_6_lines(char *path);

#endif
