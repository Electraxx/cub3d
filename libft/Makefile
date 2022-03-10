NAME=libft.a
CC=gcc
CFLAGS=-g -Wall -O0 -Wall -Wextra -Werror
RM=rm -f
SRCS= ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
		ft_memchr.c ft_memcmp.c ft_strlen.c ft_isalpha.c ft_isdigit.c \
		ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
		ft_strchr.c ft_strrchr.c ft_strncmp.c ft_strlcpy.c ft_strlcat.c \
		ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split_enhanced.c ft_itoa.c ft_strmapi.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c \
		ft_striteri.c ft_swap.c pow.c ft_abs.c ft_str_has_num.c ft_strcpy.c \
		ft_whitespace.c ft_numsize.c ft_str_contains.c ft_2dim_char_sz.c \
		ft_get_env.c ft_get_env_index.c ft_set_env.c ft_add_char.c \
		ft_free_2d_str.c ft_2dstr_to_str.c \
		ft_numsize.c ft_is_double_quote.c ft_split_utils.c	\
		ft_split.c ft_same_str.c ft_remove_char.c ft_slash_sanitize.c \
		ft_pushfreestr.c ft_get_escape.c ft_close_fd.c ft_delete_quotes.c ft_add_args.c \
		ft_is_a_quote.cft_close_fds.c ft_copy_2d_str.c \
		ft_print_2d_str.c ft_is_only_whitespace.c ft_is_str_full_num.c


OBJ = ft_memset.o ft_bzero.o ft_memcpy.o ft_memccpy.o ft_memmove.o \
		ft_memchr.o ft_memcmp.o ft_strlen.o ft_isalpha.o ft_isdigit.o \
		ft_isalnum.o ft_isascii.o ft_isprint.o ft_toupper.o ft_tolower.o \
		ft_strchr.o ft_strrchr.o ft_strncmp.o ft_strlcpy.o ft_strlcat.o \
		ft_strnstr.o ft_atoi.o ft_calloc.o ft_strdup.o ft_substr.o \
		ft_strjoin.o ft_strtrim.o ft_split_enhanced.o ft_itoa.o ft_strmapi.o \
		ft_putchar_fd.o ft_putstr_fd.o ft_putnbr_fd.o ft_putendl_fd.o \
		ft_striteri.o ft_swap.o pow.o ft_abs.o ft_str_has_num.o ft_strcpy.o \
		ft_whitespace.o ft_str_contains.o ft_2dim_char_sz.o \
		ft_get_env.o ft_get_env_index.o ft_set_env.o ft_add_char.o \
		ft_free_2d_str.o ft_2dstr_to_str.o \
		ft_numsize.o ft_is_double_quote.o ft_split_utils.o	\
		ft_split.o ft_same_str.o ft_remove_char.o ft_slash_sanitize.o \
		ft_pushfreestr.o ft_get_escape.o ft_close_fd.o ft_delete_quotes.o ft_add_args.o \
		ft_is_a_quote.o ft_close_fds.o ft_copy_2d_str.o \
		ft_print_2d_str.o ft_is_only_whitespace.o ft_is_str_full_num.o

$(NAME): $(OBJ)
		ar rc $(NAME) $(OBJ)
		ranlib $(NAME)

%.o: %.c
		$(CC) -g -I. -o $@ -c $? $(CFLAGS)

all: $(NAME)

clean:
		$(RM) $(OBJ)

fclean: clean
		$(RM) $(NAME)

re: fclean all

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) -c $(SRC)
	gcc -nostartfiles -shared -o libft.so $(OBJ)

.PHONY: clean clean