#ifndef ERROR_H
# define ERROR_H
void	invalid_map(void);
void	invalid_texture(void);

typedef enum 
{ 
    MAP_ERROR = -1,
    TEXTURE_ERROR = -2,
    COLOR_ERROR = -3,
    MISSING_TEXTURE = -4,
    MISSING_CARDINAL = -5,
    CHECK_OK = 1
} error_type;

#endif