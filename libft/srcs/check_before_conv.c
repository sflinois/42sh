/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_before_conv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/25 17:03:01 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/06 14:23:34 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		check_flag(char *format, t_pars **pars, int i, int stock)
{
	while (format[i])
	{
		if (format[i] == '+' && ((*pars)->flags & FLAG_ADD) == 0)
			stock = stock | FLAG_ADD;
		if (format[i] == '-' && ((*pars)->flags & FLAG_LESS) == 0)
			stock = stock | FLAG_LESS;
		if (format[i] == ' ' && ((*pars)->flags & FLAG_SPACE) == 0)
			stock = stock | FLAG_SPACE;
		if (format[i] == '#' && ((*pars)->flags & FLAG_DIEZ) == 0)
			stock = stock | FLAG_DIEZ;
		if (i == 0 && format[i] == '0' && ((*pars)->flags & FLAG_ZERO) == 0)
			stock = stock | FLAG_ZERO;
		if (i > 0 && (format[i - 1] > '9' || format[i - 1] < '0') && \
				format[i] == '0' && format[i - 1] != '.' && \
				((*pars)->flags & FLAG_ZERO) == 0)
			stock = stock | FLAG_ZERO;
		i++;
	}
	if ((stock & FLAG_LESS) && (stock & FLAG_ZERO))
		stock = stock - FLAG_ZERO;
	if ((stock & FLAG_ADD) && (stock & FLAG_SPACE))
		stock = stock - FLAG_SPACE;
	(*pars)->flags = stock;
	return (i);
}

int		check_modifier(char *format, t_pars **pars, int i)
{
	(*pars)->modifier[0] = '\0';
	while (format[i])
	{
		if ((format[i] == 'h' || format[i] == 'l' || format[i] == 'z' || \
					format[i] == 'j') && (*pars)->modifier[0] == '\0')
		{
			if (format[i] == 'h' && format[i + 1] == 'h')
				(*pars)->modifier[0] = 'a';
			else if (format[i] == 'l' && format[i + 1] == 'l')
				(*pars)->modifier[0] = 'b';
			else if ((format[i] == 'l' || format[i] == 'h' || format[i] == \
						'j' || format[i] == 'z') && format[i + 1] != format[i])
				(*pars)->modifier[0] = format[i];
			(*pars)->flags = (*pars)->flags | FLAG_MODIFIER;
		}
		i++;
	}
	return (i);
}

int		check_fields_prec(char *format, t_pars **pars, int i)
{
	while (format[i])
	{
		if (format[i] >= '1' && format[i] <= '9')
		{
			(*pars)->fields = ft_atoi(format + i);
			(*pars)->flags = (*pars)->flags | FLAG_NUMBER;
			while (format[i] >= '0' && format[i] <= '9')
				i++;
			i--;
		}
		if (format[i] == '.')
		{
			i++;
			(*pars)->prec = ft_atoi(format + i);
			(*pars)->flags = (*pars)->flags | FLAG_PRECI;
			while (format[i] >= '0' && format[i] <= '9')
				i++;
			i--;
		}
		i++;
	}
	check_modifier(format, pars, 0);
	return (0);
}

int		check_conversion(char *format, t_pars **pars, int i, va_list ap)
{
	static const t_conv g_conv[] = {
		{ "diouxX", int_arg },
		{ "p", p_arg },
		{ "DOU", dou_arg },
		{ "c", c_arg },
		{ "C", big_c_arg },
		{ "s", s_arg },
		{ "S", ws_arg },
		{ "%", per_arg},
		{ 0, NULL},
	};

	while (g_conv[i].line)
	{
		if (ft_strchr(g_conv[i].line, format[0]))
		{
			if ((g_conv[i].f(pars, format, ap, 0)) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}
