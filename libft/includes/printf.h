/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:44:53 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 17:45:03 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H

# define PRINTF_H
# include "libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <wchar.h>
# include <stdlib.h>
# include <string.h>

# define FLAG_ADD		1
# define FLAG_LESS		2
# define FLAG_SPACE		4
# define FLAG_ZERO		8
# define FLAG_NUMBER	16
# define FLAG_DIEZ		32
# define FLAG_PRECI		64
# define FLAG_MODIFIER	128
# define FLAG_SIGN		256
# define BUFF_SIZE		1024

typedef struct		s_pars
{
	char			buf[BUFF_SIZE];
	int				position;
	size_t			size_str;
	int				flags;
	size_t			fields;
	size_t			prec;
	char			modifier[2];
	char			sign;
	int				maj;
}					t_pars;

typedef struct		s_conv
{
	char			*line;
	int				(*f)(t_pars **pars, char *line, va_list ap, int i);
}					t_conv;

typedef struct		s_conv_int
{
	char			*line;
	char			*(*f)(t_pars **pars, char *format, va_list ap, int i);
}					t_conv_int;

int					check_flag(char *format, t_pars **pars, int i, int stock);
int					check_fields_prec(char *format, t_pars **pars, int i);
int					check_conversion(char *format, t_pars **pars, \
		int i, va_list ap);
int					c_arg(t_pars **pars, char *format, va_list ap, int i);
int					s_arg(t_pars **pars, char *format, va_list ap, int i);
int					int_arg(t_pars **pars, char *format, va_list ap, int i);
int					dou_arg(t_pars **pars, char *format, va_list ap, int i);
int					big_c_arg(t_pars **pars, char *format, va_list ap, int i);
int					ws_arg(t_pars **pars, char *format, va_list ap, int i);
int					p_arg(t_pars **pars, char *format, va_list ap, int i);
int					per_arg(t_pars **pars, char *format, va_list ap, int i);
char				*str_on_left(char *str, int i, t_pars **pars, int x);
void				flags_on_str(char *s, char *str1, t_pars **pars, size_t i);
void				fill_buf(char *str, t_pars **pars, int i);
void				fill_buf1(char *str, t_pars **pars, int size, int i);
char				*ft_itoa_base(long long int value, int base, \
		int maj, char *str);
char				*ft_utoa_base(unsigned long long int value, int base, \
		int maj, char *str);
char				*ft_reverse(char *str, char *str1, t_pars **pars, int i);
int					bigger_size(size_t size, t_pars **pars);
int					bigger_size_int(size_t size, t_pars **pars);
void				flags_int(t_pars **pars, char *f, char *str, char *str1);
char				*signed_conv(t_pars **pars, char *f, va_list ap, int i);
char				*unsigned_conv(t_pars **pars, char *f, va_list ap, int i);
char				*check_value(char *str, t_pars **pars);
char				*func_diez(char *f, char *str1, t_pars **pars, size_t i);
int					ft_wstrlen(wchar_t *str);
int					bites_in_char(wchar_t c);
int					fill_char(wchar_t c, char *str, int *i);
char				*size_of_malloc(char *str1, t_pars **pars);
char				*flags_on_str1(char *st, char *s, t_pars **pars, size_t i);
char				*flags_on_str2(char *st, char *s, t_pars **pars, size_t i);
char				*flags_on_str3(char *st, char *s, t_pars **pars, size_t i);
char				*flags_on_str4(char *st, char *s, t_pars **pars, size_t i);
char				*flags_int_1(t_pars **pars, char *str, char *s, size_t i);
char				*flags_int_2(t_pars **pars, char *str, char *s, size_t i);
char				*flags_int_3(t_pars **pars, char *str, char *s, size_t i);
char				*flags_int_4(t_pars **pars, char *str, char *s, size_t i);
char				*flags_int_5(t_pars **pars, char *str, char *s);
int					check_specifier(char *format, int i);
void				clean_all(t_pars **pars);
void				no_specifier(t_pars **pars, char *format);
void				fields_for_big_c(t_pars **pars, char *str, int size);
#endif
