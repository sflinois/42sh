/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:32:45 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 17:52:08 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/printf.h"
#include <stdarg.h>
#include <locale.h>
#include <limits.h>

int		stock_flags(char *format, t_pars **pars, int i, int j)
{
	char	*str;
	int		x;

	x = 0;
	str = NULL;
	while (format[i] == 'h' || format[i] == 'l' || format[i] == 'j' || \
			format[i] == 'z' || format[i] == ' ' || format[i] == '+' || \
			format[i] == '-' || format[i] == '#' || format[i] == '0' || \
			format[i] == '.' || (format[i] >= '0' && format[i] <= '9'))
		i++;
	if (i > 0)
	{
		if ((str = (char*)malloc(sizeof(char) * (i + 1))) == NULL)
			return (0);
		while (j < i)
		{
			str[j] = format[j];
			j++;
		}
		str[j] = '\0';
		check_flag(str, pars, 0, 0);
		check_fields_prec(str, pars, 0);
		free(str);
	}
	return (j);
}

int		copy_string1(t_pars **pars, char *format, va_list ap, int *i)
{
	int		j;

	j = 0;
	j = (*i);
	clean_all(pars);
	j++;
	if (format[j] != '\0')
	{
		j = j + stock_flags(format + j, pars, 0, 0);
		if ((check_specifier(format + j, 0)) == 1 && format[j] != '\0')
		{
			if ((check_conversion(format + j++, pars, 0, ap)) == -1)
				return (-1);
		}
		else if ((format[j] >= 'a' && format[j] <= 'z') || (format[j] >= 'A' \
					&& format[j] <= 'Z'))
		{
			no_specifier(pars, format + j++);
		}
	}
	return (j - (*i));
}

int		copy_string(char *format, t_pars **pars, int j, va_list ap)
{
	(*pars)->position = 0;
	while (format[j])
	{
		if (format[j] == '%')
		{
			if ((j = j + (copy_string1(pars, format, ap, &j))) == -1)
				return (-1);
		}
		else
		{
			if ((*pars)->position + 1 == BUFF_SIZE)
			{
				write(1, (*pars)->buf, (*pars)->position);
				(*pars)->position = 0;
			}
			(*pars)->buf[(*pars)->position] = format[j];
			(*pars)->position++;
			j++;
		}
	}
	(*pars)->buf[(*pars)->position] = '\0';
	write(1, (*pars)->buf, (*pars)->position);
	return (0);
}

int		ft_printf(const char *format, ...)
{
	t_pars		*pars;
	va_list		ap;
	int			ret;

	if ((pars = (t_pars*)malloc(sizeof(t_pars))) == NULL)
		return (0);
	ft_bzero(pars, sizeof(pars));
	va_start(ap, format);
	if ((copy_string((char*)format, &pars, 0, ap)) == -1)
		return (-1);
	ret = (pars->position);
	free(pars);
	va_end(ap);
	return (ret);
}
