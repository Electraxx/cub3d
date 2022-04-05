#ifndef CUB3D_H
# define CUB3D_H
# include <libft.h>
# include <get_next_line.h>
# include <fcntl.h>
# include "error.h"
# include "colorValidation.h"
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx/mlx.h"
# include <pthread.h>
# include <math.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define PI 3.141592653589

#define W_KEY 13
#define S_KEY 1
#define A_KEY 0
#define D_KEY 2

#define SPEED 0.3
#define ROT_SPEED 0.125

typedef struct s_color{
	int	a;
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
	size_t		caseHeight;
	size_t		caseWidth;
	size_t		mapMaxWidth;
	size_t		mapMaxHeight;
} t_config;

typedef struct s_cardi_check{
	int *val;
	char **cardi;
} t_cardi_check;

// int g_debug = 0;

typedef struct s_player
{
	double	posX;
	double	posY;
	double	v_angle;
	double	ori;
}	t_player;

typedef struct s_camera
{
	double	planeX;
	double	planeY;
	double	dirX;
	double	dirY;
}	t_camera;

typedef struct	s_image {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_image;

typedef struct s_mlxp
{
	void	*mlx_ptr;
	void	*win_ptr;
	char	**map;
	int		wh;
	int		ww;
}	t_mlxp;

typedef struct s_assets
{
	void	*wallText;
}	t_assets;

typedef struct s_game
{
	char		**map;
	t_player	*player;
	t_image		*buffer;
	t_mlxp		*mlxp;
	t_config	*config;
	t_camera	*camera;
	t_image *rayIgm;
	t_image *minimap;
	t_assets *textures;
	uint32_t textbuff[WINDOW_HEIGHT][WINDOW_WIDTH];
}	t_game;

void		init_cardi_struct(t_cardi_check *cardi);
error_type	texture_check(char *t_path, t_cardi_check *check_cardi);
int			check_all_cardi(t_cardi_check *cardi);

// colorValidations.c
error_type 		is_color_valid(char *color_line);

// mapValidation.c
error_type		ft_parse_first_6_lines(int fd, t_cardi_check *cardiCheck);
error_type		parse_map(int fd, int lines_num, char ***map);
void			fill_map(char ***map);
void			player_setpos(char **map, t_player *player);

// textureValidation.c
int 			is_valid_cardinal(char *cardinal);

// debug.c
void			ft_print_map(char **map);

// fileParsing.c
error_type		ft_parse_file(char *path, t_cardi_check *cardiCheck, t_game *game);

// error.c
void			print_error_exit(error_type error);

//render2d
void			my_mlx_pixel_put(t_image *image, int x, int y, int color);
int				max_width(char **map);
int				max_height(char **map);

//movement.c
int				key_hook(int keycode, t_game *game);

#endif
