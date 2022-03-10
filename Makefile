SRCS_DIR	= sources/
SRCS_FILES	= main.c init.c error.c mapValidation.c colorValidation.c textureValidation.c configValidation.c
SRCS		= ${patsubst %, ${SRCS_DIR}%, ${SRCS_FILES}}

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
OBJSB		= ${BONUS:.c=.o}
OBJFT		= ${FT:.c=.o}

NAME		= cub3d

CC		= gcc
AR		= ar rcs
CP		= cp -f
RM		= rm -f

CFLAGS		= -Wall -Wextra -Werror -g

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} ${OBJFT}
		${MAKELIBX} all
		${MAKELIB} all
		${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${OBJFT} -Lminilibx -lmlx -framework OpenGL -framework AppKit

all:		${NAME}

bonus:		${NAME}

clean:
		${RM} ${OBJS} ${OBJFT}
		${MAKELIBX} clean

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:		all bonus clean fclean re
