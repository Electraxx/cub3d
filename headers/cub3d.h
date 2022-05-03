#ifndef CUB3D_H
# define CUB3D_H
# include <libft.h>
# include <get_next_line.h>
# include <fcntl.h>
# include "error.h"
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx/mlx.h"
# include <pthread.h>
# include <math.h>

# define W_W 640
# define W_H 480

# define PI 3.141592653589

# define W_KEY 13
# define S_KEY 1
# define A_KEY 0
# define D_KEY 2

# define SPEED 0.1
# define ROT_SPEED 0.05

typedef struct s_point {
	double	x;
	double	y;
}				t_point;

typedef enum e_error_type
{
	MAP_ERROR = -1,
	TEXTURE_ERROR = -2,
	COLOR_ERROR = -3,
	MISSING_TEXTURE = -4,
	MISSING_CARDINAL = -5,
	PLAYER_ERROR = -6,
	WALL_ERROR = -7,
	FORMAT_ERROR = -8,
	CHECK_OK = 1
} error_type;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
} t_image;

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
	char	firstDir;
	size_t	caseHeight;
	size_t	caseWidth;
	size_t	mapMaxWidth;
	size_t	mapMaxHeight;
} t_config;

typedef struct s_cardi_check{
	int		*val;
	char	**cardi;
} t_cardi_check;

typedef struct s_player
{
	t_point			pos;
	int				health;
	char			dirState;
	e_action_index	*current_action;
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
	t_image		coll_buffer;
	t_mlxp		mlxp;
	t_config	config;
	t_camera	camera;
	t_image		ray_img;
	t_image		*minimap;
	t_image		lifebar;
	t_assets	textures;
}	t_game;

// init.c
void			init_cardi_struct(t_cardi_check *cardi);
void			init_config_struct(t_config *cfg);
error_type		texture_check(char *t_path, t_cardi_check *check_cardi);

// colorValidations.c
error_type		is_color_valid(char *color_line);
void			load_color(t_config *cfg, char *color, char type);

// mapValidation.c
error_type		ft_parse_first_6_lines(int fd, t_cardi_check *cardiCheck, t_config *cfg);
error_type		parse_map(int fd, int lines_num, char ***map);
void			fill_map(char ***map);

// textureValidation.c
int				is_valid_cardinal(char *cardinal);
void			load_texture(t_config *cfg, char *path, char type);

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
void			move(t_game *game, int dir);
void			turncamera(t_game *game, int dir);
int				key_relase(int kc, t_game *game);

//drawing.c
void			draw(void *g);
void			verline(t_raycast_data *rdata, t_image *buf,t_mlxp *mlx, t_config *cfg);
unsigned int	get_pixel_color(int x, int y, char *firstpixel);
int				*load_line_texture(int len, int step, int texPos, int texX, int side, t_image *texture);
void			draw_view(t_raycast_data *rdata, t_game *game);

//textures.c
void			load_textures(t_game *game);
void			load_asset(t_image *asset, char *path, t_mlxp *mlxp);
void			fix_png(t_image *img);
t_image			*get_ray_texture(t_assets *assets, t_raycast_data *rdata);
t_image			*get_texture(char c, t_assets *text);

//ui.c
void			ft_draw_lifebar(t_game *game);
int				get_hp(int kc, t_game *game);

//directions.c
char			get_adjacent_cardinal(int vec, char curr);
void			set_player_dir(t_camera *camera, char goal);
void			get_player_orientation(char **map, t_config *cfg);

//helper.c
int				exit_game(int kc, t_game *game);
unsigned int	creatergba(int r, int g, int b, int a);
void			init_buffer(t_image *buf, void *mlxp, int width, int height);

//todo
void			do_action(t_game *game);

//raycast.c
void			calc_sidedist(t_raycast_data *rdata, t_point pos);
void			check_hit(t_raycast_data *rayData, char **map);
void			calc_line(t_raycast_data *rayData);
void			load_line(t_raycast_data *rayData, t_point pos, t_game *game);
void			load_text_line(t_raycast_data *rayData, t_image *text);

//player.c
void			player_setpos(char **map, t_player *player);
int				player_check(char **map);

#endif
