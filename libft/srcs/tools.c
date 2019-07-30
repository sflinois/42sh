/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:41:14 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/04 15:56:05 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		ft_wstrlen(wchar_t *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*size_of_malloc(char *str1, t_pars **pars)
{
	char	*str;
	int		size;
	int		a;

	size = ft_strlen(str1);
	a = bigger_size(size, pars);
	(*pars)->size_str = a;
	if ((str = ft_strnew(a)) == NULL)
		return (0);
	return (str);
}

int		check_specifier(char *format, int i)
{
	if (format[i] == 'D' || format[i] == 'O' || format[i] == 'U' || \
			format[i] == 'd' || format[i] == 'i' || format[i] == 'o' || \
			format[i] == 'u' || format[i] == 'x' || format[i] == 'X' || \
			format[i] == 'p' || format[i] == 's' || format[i] == 'c' || \
			format[i] == 'S' || format[i] == 'C' || format[i] == '%')
		return (1);
	return (0);
}

int		bigger_size(size_t size, t_pars **pars)
{
	if ((((*pars)->flags & FLAG_PRECI) == 0) && ((*pars)->flags & \
				FLAG_NUMBER) == 0)
		return (size);
	if ((((*pars)->flags & FLAG_PRECI) == 0) && (*pars)->flags & FLAG_NUMBER)
	{
		if (size >= (*pars)->fields)
			return (size);
		if ((*pars)->fields > size)
			return ((*pars)->fields);
	}
	if ((*pars)->flags & FLAG_PRECI && ((*pars)->flags & FLAG_NUMBER) == 0)
		return ((*pars)->prec);
	if (size > (*pars)->prec && size > (*pars)->fields)
	{
		if ((*pars)->prec > (*pars)->fields)
			return ((*pars)->prec);
		else
			return (size);
	}
	if ((*pars)->prec > size && (*pars)->prec >= (*pars)->fields)
		return ((*pars)->prec);
	if ((*pars)->fields > size)
		return ((*pars)->fields);
	return (0);
}

int		int_arg(t_pars **pars, char *format, va_list ap, int i)
{
	static const t_conv_int g_conv_int[] = {
	{"di", signed_conv},
	{"ouxX", unsigned_conv},
	{0, NULL}
	};

	while (g_conv_int[i].line)
	{
		if (ft_strchr(g_conv_int[i].line, format[0]))
		{
			g_conv_int[i].f(pars, format, ap, 0);
		}
		i++;
	}
	return (0);
}
