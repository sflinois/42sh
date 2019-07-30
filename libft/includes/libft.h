/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 20:16:46 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 17:44:16 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# define BUFF_SIZE_GNL 10

typedef char		t_bool;

# define TRUE		1
# define FALSE		0

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

int					ft_atoi(const char *str);
void				ft_bzero(void *s, size_t n);
char				*ft_itoa(int n);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isprint (int c);
int					ft_tolower(int c);
int					ft_toupper(int c);
void				*ft_memalloc(size_t size);
void				*ft_memccpy(void *dest, const void *src, int c, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void*s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				ft_memdel(void **ap);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memset(void *s, int c, size_t n);
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
void				ft_lstadd(t_list **alst, t_list *n);
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
size_t				ft_strlen(const char *s);
int					ft_strclen(const char *src, int c);
char				*ft_strncat(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
size_t				ft_strlcat(char *dest, const char *src, size_t size);
char				*ft_strchr(const char *str, int c);
char				*ft_strrchr(const char *str, int c);
int					ft_strchrstr(char *s1, char *s2);
char				*ft_strrchr2(const char *str, int c);
char				*ft_strstr(const char *haystack, const char *needle);
char				*ft_strnstr(const char *k, const char *e, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strdup(const char *s);
char				*ft_strndup(char *src, int len);
char				*ft_strcdup(const char *src, int c);
char				*ft_strnew(size_t size);
void				ft_strclr(char *s);
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void(*f)(unsigned int, char*));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char				*ft_strsub(char const *s, unsigned int c, size_t l, int x);
char				*ft_strtrim(char const *s, int x);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoinfree(char *s1, char *s2, int i);
char				**ft_create_tab(int l, int c);
char				**ft_create_first_step_tab(int x);
char				*ft_unsplit_tab(char **tabb);
char				**ft_strsplit(char const *s, char c);
char				**ft_strsplit_miss(char const *s, char c);
extern char			**ft_strexplode(char const *s, char *c);
void				ft_free_tab(char **tabb);
void				ft_strdel(char **as);
void				ft_print_map(char **tabb);
int					get_next_line(const int fd, char **line);
int					check_if_int(char *str);
t_bool				check_full_space(char *str, int f);
void				ft_close_load_directory(DIR *rep);
int					ft_check_right_exec(char *str);
int					ft_printf(const char *format, ...);
char				*ft_strjoinmiddle(char *s1, char *s2, int c, int d);
char				find_char_in_str(char c, char *str);
int					go_next_same_char(char *str, int *a, char c);
int					echap_charac(char *str, int i);
void				delete_space_local(char *str);
int					protect_atoi(const char *str, int protect);
int					next_c_wo_space(char *str, char *check);
int					if_alpha_or_digit(char c);
int					nb_arg_tab(char **tabb);
#endif
