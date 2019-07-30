/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_c_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:20:57 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/06 15:00:59 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		fill_char(wchar_t c, char *str, int *i)
{
	if (c <= 255)
		str[(*i)++] = c;
	else if (c <= 2047)
	{
		str[(*i)++] = ((c >> 6) & 31) + 0xC0;
		str[(*i)++] = (c & 0x3F) + 0x80;
	}
	else if (c <= 0xFFFF)
	{
		str[(*i)++] = ((c >> 12) & 15) + 0xE0;
		str[(*i)++] = ((c >> 6) & 63) + 128;
		str[(*i)++] = (c & 63) + 128;
	}
	else if (c <= 0x10FFFF)
	{
		str[(*i)++] = ((c >> 18) & 7) + 240;
		str[(*i)++] = ((c >> 12) & 63) + 128;
		str[(*i)++] = ((c >> 6) & 63) + 128;
		str[(*i)++] = (c & 63) + 128;
	}
	else
		return (-1);
	return (0);
}

int		big_c_arg(t_pars **pars, char *format, va_list ap, int i)
{
	wchar_t		c;
	char		str[7];

	(void)format;
	(void)pars;
	ft_bzero(str, 7);
	c = 0;
	c = va_arg(ap, wchar_t);
	i = 0;
	if (c >= 0xd800 && c <= 0xdfff)
		return (-1);
	if (c >= 0)
	{
		if ((fill_char(c, str, &i)) == -1)
			return (-1);
		if ((*pars)->flags & FLAG_NUMBER && (*pars)->fields > (size_t)i)
		{
			fields_for_big_c(pars, str, i);
			return (0);
		}
		fill_buf1(str, pars, i, 0);
		return (0);
	}
	return (-1);
}

int		bites_in_char(wchar_t c)
{
	int		j;

	j = 0;
	if (c <= 127)
		j = 1;
	else if (c <= 2047)
		j = 2;
	else if (c <= 0xFFFF)
		j = 3;
	else if (c <= 0x10FFFF)
		j = 4;
	return (j);
}

char	*c_arg1(t_pars **pars, char *str, va_list ap, int *j)
{
	size_t	i;

	i = 0;
	if ((str = ft_strnew((*pars)->fields + 1)) == NULL)
		return (0);
	while ((size_t)i < (*pars)->fields - 1 && (*pars)->flags & FLAG_ZERO)
	{
		str[i++] = '0';
	}
	while ((size_t)i < (*pars)->fields - 1)
		str[i++] = ' ';
	str[i++] = va_arg(ap, int);
	str[i] = '\0';
	if ((*pars)->flags & FLAG_LESS)
		str = str_on_left(str, 0, pars, i);
	(*j) = (int)i;
	return (str);
}

int		c_arg(t_pars **pars, char *format, va_list ap, int i)
{
	char	*str;

	(void)format;
	str = NULL;
	if ((*pars)->modifier[0] == 'l')
	{
		big_c_arg(pars, format, ap, 0);
		return (0);
	}
	if ((*pars)->flags & FLAG_NUMBER)
		str = c_arg1(pars, str, ap, &i);
	else
	{
		if ((str = ft_strnew(2)) == NULL)
			return (0);
		str[i++] = va_arg(ap, int);
		str[i] = '\0';
	}
	fill_buf1(str, pars, i, 0);
	free(str);
	return (0);
}
