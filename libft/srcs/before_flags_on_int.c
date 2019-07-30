/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   before_flags_on_int.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 09:37:04 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 17:47:03 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

void	check_modifier1(t_pars **pars, char *str, va_list ap)
{
	long long int	a;

	a = 0;
	a = va_arg(ap, long long int);
	if (a < 0 && (*pars)->flags & FLAG_SPACE)
		(*pars)->flags = (*pars)->flags - FLAG_SPACE;
	if ((*pars)->modifier[0] == 'a')
		ft_itoa_base((signed char)a, 10, 0, str);
	else if ((*pars)->modifier[0] == 'b')
		ft_itoa_base((long long int)a, 10, 0, str);
	else if ((*pars)->modifier[0] == 'h')
		ft_itoa_base((short)a, 10, 0, str);
	else if ((*pars)->modifier[0] == 'l')
		ft_itoa_base((long)a, 10, 0, str);
	else if ((*pars)->modifier[0] == 'j')
		ft_itoa_base((intmax_t)a, 10, 0, str);
	else if ((*pars)->modifier[0] == 'z')
		ft_itoa_base((ssize_t)a, 10, 0, str);
	else if ((*pars)->modifier[0] == 'M')
		ft_itoa_base((long)a, 10, 0, str);
	else if (((*pars)->flags & FLAG_MODIFIER) == 0)
		ft_itoa_base((int)a, 10, 0, str);
	if (a == 0 && (*pars)->flags & FLAG_PRECI && (*pars)->prec == 0)
		str[0] = '\0';
}

char	*signed_conv(t_pars **pars, char *format, va_list ap, int i)
{
	char			str[129];
	char			*str1;
	char			*str2;
	int				size;

	ft_bzero(str, 129);
	check_modifier1(pars, str, ap);
	if ((str1 = ft_strnew(ft_strlen(str) + 1)) == NULL)
		return (NULL);
	str1 = ft_reverse(str, str1, pars, 0);
	size = ft_strlen(str);
	(*pars)->size_str = size;
	i = bigger_size_int(size, pars);
	if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
		i++;
	if ((*pars)->flags & FLAG_SPACE)
		i++;
	if ((str2 = ft_strnew(i + 1)) == NULL)
		return (NULL);
	if ((*pars)->flags & FLAG_DIEZ)
		(*pars)->flags = (*pars)->flags - FLAG_DIEZ;
	flags_int(pars, format, str1, str2);
	return (0);
}

void	check_modifier_u1(t_pars **pars, char *str, int *i, \
		unsigned long long int a)
{
	if ((*pars)->modifier[0] == 'a')
		ft_utoa_base((unsigned char)a, 10 + (*i), (*pars)->maj, str);
	else if ((*pars)->modifier[0] == 'b')
		ft_utoa_base((unsigned long long)a, 10 + (*i), (*pars)->maj, str);
	else if ((*pars)->modifier[0] == 'h')
		ft_utoa_base((unsigned short)a, 10 + (*i), (*pars)->maj, str);
	else if ((*pars)->modifier[0] == 'l')
		ft_utoa_base((unsigned long)a, 10 + (*i), (*pars)->maj, str);
	else if ((*pars)->modifier[0] == 'j')
		ft_utoa_base((uintmax_t)a, 10 + (*i), (*pars)->maj, str);
	else if ((*pars)->modifier[0] == 'z')
		ft_utoa_base((ssize_t)a, 10 + (*i), (*pars)->maj, str);
	else if ((*pars)->modifier[0] == 'M')
		ft_utoa_base((unsigned long)a, 10 + (*i), (*pars)->maj, str);
	else if (((*pars)->flags & FLAG_MODIFIER) == 0)
		ft_utoa_base((unsigned int)a, 10 + (*i), (*pars)->maj, str);
}

void	check_modifier_u(char *format, t_pars **pars, char *str, va_list ap)
{
	unsigned long long int		a;
	int							i;

	a = 0;
	i = 0;
	if (format[0] == 'x' || format[0] == 'X')
		i = 6;
	else if (format[0] == 'o' || format[0] == 'O')
		i = -2;
	(*pars)->maj = format[0] == 'X' ? 1 : 0;
	a = va_arg(ap, unsigned long long int);
	if (a == 0 && (*pars)->flags & FLAG_PRECI && (*pars)->prec == 0)
		str[0] = '\0';
	else
		check_modifier_u1(pars, str, &i, a);
	if ((*pars)->flags & FLAG_DIEZ && format[0] != 'O' && \
			format[0] != 'o' && a == 0)
		(*pars)->flags = (*pars)->flags - FLAG_DIEZ;
	(*pars)->modifier[0] = '\0';
}

char	*unsigned_conv(t_pars **pars, char *format, va_list ap, int i)
{
	char		str[129];
	char		*str1;
	char		*str2;
	int			size;

	ft_bzero(str, 129);
	check_modifier_u(format, pars, str, ap);
	if ((str1 = ft_strnew(ft_strlen(str) + 1)) == NULL)
		return (NULL);
	str1 = ft_reverse(str, str1, pars, 0);
	size = ft_strlen(str1);
	i = bigger_size_int(size, pars);
	(*pars)->size_str = size;
	if ((str2 = ft_strnew(i + 1)) == NULL)
		return (NULL);
	if ((*pars)->flags & FLAG_ADD && format[0] != 'D')
		(*pars)->flags = (*pars)->flags - FLAG_ADD;
	if ((*pars)->flags & FLAG_SPACE && format[0] != 'D')
		(*pars)->flags = (*pars)->flags - FLAG_SPACE;
	if ((*pars)->flags & FLAG_DIEZ && (format[0] == 'u' || \
				format[0] == 'D' || format[0] == 'U'))
		(*pars)->flags = (*pars)->flags - FLAG_DIEZ;
	flags_int(pars, format, str1, str2);
	return (0);
}
