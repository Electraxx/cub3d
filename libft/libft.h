/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbrechbu <qbrechbu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 02:33:00 by qbrechbu          #+#    #+#             */
/*   Updated: 2022/03/10 11:53:50 by qbrechbu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_split{
	int	i;
	int	count;
}	t_split;

int		ft_isalnum(int c);
int		ft_atoi(const char *str);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc( size_t count, size_t size );
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
char	*ft_memchr(const char *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memccpy(void *dst, const void *src, int c, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
void	*ft_memset(void *b, int c, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strrchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_nbrofmatchingchars(char const *str, char *set);
int		ft_nbrofmatchingchar(char const *str, char set);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split_enhanced(char *s, char c);
char	**ft_split(char const *s, char c);
char	*ft_itoa(int n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putnbr_fd(int n, int fd);
void	ft_swap(int *a, int *b);
int		poww(int nbr, int pow);
size_t	absolute(int n);
int		ft_str_has_num(char *str);
char	*ft_strcpy(const char *ori);
int		ft_whitespace(char c);
int		ft_numsize(int n);
int		ft_atoi_check_size(char *str);
int		ft_str_contains(char *str, char *set);
int		ft_2dim_char_sz(char **split_tab);
char	*ft_get_env(char **env, char *key);
int		ft_get_env_index(char **entries, char *key);
void	ft_set_env(char **env, char *key, char *value);
int		ft_add_char(char **str, char added_char);
void	ft_free_2d_str(char **strs);
char	*ft_2dstr_to_str(char **tab);
int		is_double_quote(char const *s, int j, char c);
int		inc_count(char *s, int *j, t_split *counts);
int		ft_get_first_char_index(char *str, char c);
void	ft_delete_quotes(char **words);
int		ft_same_str(char *str1, char *str2);
void	ft_remove_char(char **str, unsigned int index);
void	ft_2d_slash_sanitize(char **str);
void	ft_slash_sanitize(char **str);
char	ft_get_escape(char c);
void	ft_close_fd(int fd);
int		ft_pushfreestr(char **str, char *freestr);
char	**ft_add_args(char **args, char *new);
int		ft_is_a_quote(char c);
int		ft_get_first_char_index(char *str, char c);
int		get_quote_ret(int i, char **s);
void	ft_close_fds(int fd1, int fd2);
char	**ft_copy_2d_str(char **ori);
void	ft_print_2d_str(char **strs, int fd, char *prompt);
int		ft_is_only_whitespace(char *str);
int		ft_is_str_full_num(char *str);
#endif