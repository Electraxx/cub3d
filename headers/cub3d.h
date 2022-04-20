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

#define SPEED 0.1
#define ROT_SPEED 0.05

typedef struct	s_point {
	double x;
	double y;
}				t_point;

typedef struct	s_image {
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
	int 	width;
	int 	height;
}				t_image;

typedef struct	s_line_texture_data {
	int texX;
	int texY;
	double wallX;
	double step;
	double texPos;
	uint32_t *pixelArray;
}				t_line_texture_data;

typedef struct	s_line_data {
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	double	perpWallDist;
	t_line_texture_data line_text_data;

}				t_line_data;

typedef struct	s_raycast_data {
	double  sideDistX;
	double  sideDistY;
	double	rayDirX;
	double	rayDirY;
	double  deltaDistX;
	double  deltaDistY;
	double  cameraX;
	int     mapX;
	int     mapY;
	double  stepX;
	double  stepY;
	int     hit;
	int     side;
	int 	line;
	t_line_data line_data;
}				t_raycast_data;

typedef enum e_action_index{
	FRONT_INDEX,
	BACK_INDEX,
	R_LEFT_INDEX,
	R_RIGHT_INDEX,
	NONE
} e_action_index;

typedef struct s_color{
	int	a;
	int	r;
	int	g;
	int	b;
} t_color;

typedef struct s_config{
	size_t	floor;
	size_t	ceiling;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char 	firstDir;
	size_t		caseHeight;
	size_t		caseWidth;
	size_t		mapMaxWidth;
	size_t		mapMaxHeight;
} t_config;

typedef struct s_cardi_check{
	int *val;
	char **cardi;
} t_cardi_check;

typedef struct s_player
{
	t_point pos;
    int     health;
	char 	dirState;
	e_action_index *current_action;
}	t_player;

typedef struct s_camera
{
	double	planeX;
	double	planeY;
	double	dirX;
	double	dirY;
}	t_camera;

typedef struct s_mlxp
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlxp;

typedef struct s_assets
{
	t_image	*N_texture;
	t_image	*S_texture;
	t_image	*E_texture;
	t_image	*W_texture;
}	t_assets;

typedef struct s_game
{
	char		**map;
	t_player	player;
	t_image		*buffer;
	t_mlxp		*mlxp;
	t_config	config;
	t_camera	*camera;
	t_image *rayIgm;
	t_image *minimap;
    t_image lifebar;
    t_image *texture;
	t_assets *textures;
}	t_game;

void			init_cardi_struct(t_cardi_check *cardi);
error_type		texture_check(char *t_path, t_cardi_check *check_cardi);
int				check_all_cardi(t_cardi_check *cardi);

// colorValidations.c
error_type		is_color_valid(char *color_line);

// mapValidation.c
error_type		ft_parse_first_6_lines(int fd, t_cardi_check *cardiCheck, t_config *cfg);
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
void 			move(t_game *game, int dir);
void			turnCamera(t_game *game, int dir);

//main.c
void            ft_draw_lifebar(t_game *game);

//drawing.c
void            draw(void *g);
void			ft_verline(t_raycast_data *rdata, t_image *buffer,t_mlxp *mlx, t_config *cfg);
unsigned int 	get_pixel_color(int x, int y, char *firstpixel);
void    		set_pixel_color(int x, int y, char *firstpixel, unsigned int newVal);
int				*load_line_texture(int len, int step, int texPos, int texX, int side, t_image *texture);
void			draw_view(t_raycast_data *rdata, t_game *game);



//todo
char	get_adjacent_cardinal(int vec, char curr);
void do_action(t_game *game);
unsigned int createRGBA(int r, int g, int b, int a);


#endif
