#ifndef CUBE3D_H
#define CUBE3D_H
#include "../libft/libft.h"
#include "error.h"
#include "colorValidation.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct s_color{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_config{
    t_color *floor;
    t_color *ceiling;
    char     *path_no;
    char     *path_so;
    char     *path_we;
    char     *path_ea;
    char     **map;
} t_config;

typedef struct s_cardi_check{
    int *val;
    char **cardi;
} t_cardi_check;

void		init_cardi_struct(t_cardi_check *cardi);
error_type	texture_check(char *t_path, t_cardi_check *check_cardi);
int			check_all_cardi(t_cardi_check *cardi);

#endif
