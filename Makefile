SRCS_DIR	= sources/
SRCS_DIR_GNL = sources/gnl/
SRCS_FILES_GNL = get_next_line.c
SRCS_FILES	=	main.c init.c error.c player.c mapValidation.c colorValidation.c textureValidation.c \
				fileParsing.c movement.c drawing.c textures.c ui.c directions.c helper.c pixels.c \
				raycast.c
SRCS		= ${patsubst %, ${SRCS_DIR}%, ${SRCS_FILES}}
SRCS_GNL = ${patsubst %, ${SRCS_DIR_GNL}%, ${SRCS_FILES_GNL}}

BONUS_DIR	= ./
BONUS_FILES	= 
BONUS		= ${patsubst %, ${BONUS_DIR}%, ${BONUS_FILES}}

FT_DIR	= libft/
FT_FILES	= 
FT			= ${wildcard libft/*.c}

LIBFT		= ./libft
MAKELIB		= ${MAKE} -C ${LIBFT}

LIBX		= ./minilibx
MAKELIBX	= ${MAKE} -C ${LIBX}
HEADS		= ./

OBJS		= ${SRCS:.c=.o}
OBJS_GNL	= ${SRCS_GNL:.c=.o}
OBJSB		= ${BONUS:.c=.o}
OBJFT		= ${FT:.c=.o}

NAME		= cub3d

CC		= /Users/vvermot-/sgoinfre/lgyger/.brew/Cellar/llvm/13.0.1_1/bin/clang -fsanitize=leak -I ./headers/ -I ${SRCS_DIR_GNL} -I ${FT_DIR}
AR		= ar rcs
CP		= cp -f
RM		= rm -f

CFLAGS		= -g3 -Wall -Wextra -Werror

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:  ${OBJS} ${OBJS_GNL} ${OBJFT}
		${MAKELIBX} all
		${MAKELIB} all
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${OBJS_GNL} ${OBJFT} -Lminilibx -lmlx -framework OpenGL -framework AppKit

all:		${NAME}

bonus:		${NAME}

clean:
		${RM} ${OBJS} ${OBJFT} ${OBJS_GNL}

fclean:		clean
		${RM} ${NAME}

re:		fclean ${OBJS} ${OBJS_GNL} ${OBJFT}
		${MAKELIB} all
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${OBJS_GNL} ${OBJFT} -Lminilibx -lmlx -framework OpenGL -framework AppKit

.PHONY:		all bonus clean fclean re
