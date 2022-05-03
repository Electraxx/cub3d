/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 16:20:58 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/05/03 16:21:03 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <libft.h>
# include <get_next_line.h>
# include <fcntl.h>
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
}	t_error_type;

typedef struct s_image {
	void	*img;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
}	t_image;

typedef struct s_line_texture_data {
	int			texx;
	int			texy;
	double		wallx;
	double		step;
	double		texpos;
	uint32_t	*pixelarray;
}				t_line_texture_data;

typedef struct s_line_data {
	int					lineheight;
	int					drawstart;
	int					drawend;
	double				perpwalldist;
	t_line_texture_data	line_text_data;

}	t_line_data;

typedef struct s_raycast_data {
	double		sidedistx;
	double		sidedisty;
	double		raydirx;
	double		raydiry;
	double		deltadistx;
	double		deltadisty;
	double		camerax;
	int			mapx;
	int			mapy;
	double		stepx;
	double		stepy;
	int			hit;
	int			side;
	int			line;
	t_line_data	line_data;
}	t_raycast_data;

typedef enum e_action_index{
	FRONT_INDEX,
	BACK_INDEX,
	R_LEFT_INDEX,
	R_RIGHT_INDEX,
	NONE
}	t_action_index;

typedef struct s_config{
	size_t	floor;
	size_t	ceiling;
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	char	firstdir;
}	t_config;

typedef struct s_cardi_check{
	int		*val;
	char	**cardi;
}	t_cardi_check;

typedef struct s_player
{
	t_point			pos;
	int				health;
	t_action_index	*current_action;
}	t_player;

typedef struct s_camera
{
	double	planex;
	double	planey;
	double	dirx;
	double	diry;
}	t_camera;

typedef struct s_mlxp
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_mlxp;

typedef struct s_assets
{
	t_image	*n_texture;
	t_image	*s_texture;
	t_image	*e_texture;
	t_image	*w_texture;
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
	t_image		lifebar;
	t_assets	textures;
}	t_game;

// init.c
void			init_cardi_struct(t_cardi_check *cardi);
void			init_config_struct(t_config *cfg);
t_error_type	texture_check(char *t_path, t_cardi_check *check_cardi);

// colorValidations.c
t_error_type	is_color_valid(char *color_line);
void			load_color(t_config *cfg, char *color, char type);

// mapValidation.c
t_error_type	ft_parse_first_6_lines(int fd, t_cardi_check *ca, t_config *c);
t_error_type	parse_map(int fd, int lines_num, char ***map);
void			fill_map(char ***map);

// textureValidation.c
int				is_valid_cardinal(char *cardinal);
void			load_texture(t_config *cfg, char *path, char type);

// fileParsing.c
t_error_type	ft_parse_file(char *path, t_cardi_check *cardi, t_game *game);

// error.c
void			print_error_exit(t_error_type error);

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
void			verline(t_raycast_data *r, t_image *b, t_mlxp *m, t_config *c);
unsigned int	get_pixel_color(int x, int y, char *firstpixel);
void			draw_view(t_raycast_data *rdata, t_game *game);

//textures.c
void			load_textures(t_game *game);
void			load_asset(t_image *asset, char *path, t_mlxp *mlxp);
void			fix_png(t_image *img);
t_image			*get_ray_texture(t_assets *assets, t_raycast_data *rdata);
t_image			*get_texture(char c, t_assets *text);

//ui.c
void			ft_draw_lifebar(t_game *game);

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
