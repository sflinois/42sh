/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_int_func_diez.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:48:57 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/04 18:50:15 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*func_diez1_1(char *dst, char *format, char *str1)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (str1[i] == ' ' && str1[i + 1] == ' ')
	{
		while (str1[i + 2] == ' ')
			dst[j++] = str1[i++];
		dst[j++] = '0';
		if (format[0] != 'p')
			dst[j++] = format[0];
		else
			dst[j++] = 'x';
		i = i + 2;
		while (str1[i])
			dst[j++] = str1[i++];
		dst[j] = '\0';
	}
	return (dst);
}

char	*func_diez1(char *dst, char *format, char *str1)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (str1[i] == ' ' && str1[i + 1] != ' ')
	{
		dst[j++] = '0';
		if (format[0] != 'p')
		{
			dst[j++] = format[0];
			i++;
		}
		else
		{
			dst[j++] = 'x';
			i++;
		}
		while (str1[i])
			dst[j++] = str1[i++];
		dst[j] = '\0';
	}
	else
		dst = func_diez1_1(dst, format, str1);
	return (dst);
}

char	*func_diez2(char *dst, char *format, char *str1, t_pars **pars)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	dst[j++] = '0';
	if (format[0] != 'p')
	{
		dst[j++] = format[0];
		if ((*pars)->flags & FLAG_NUMBER && ((*pars)->flags & FLAG_PRECI) \
				== 0 && str1[i] == '0' && str1[i + 1] == '0')
			i = i + 2;
	}
	else
		dst[j++] = 'x';
	while (str1[i])
		dst[j++] = str1[i++];
	dst[j] = '\0';
	return (dst);
}

char	*func_diez(char *format, char *str1, t_pars **pars, size_t i)
{
	char	*dst;
	size_t	j;

	j = 0;
	if ((dst = ft_strnew(ft_strlen(str1) + 3)) == NULL)
		return (NULL);
	if ((format[0] != 'o' && format[0] != 'O') && ((str1[i] == ' ' && \
			str1[i + 1] != ' ') || (str1[i] == ' ' && str1[i + 1] == ' ')))
		dst = func_diez1(dst, format, str1);
	else if (format[0] != 'o' && format[0] != 'O')
		dst = func_diez2(dst, format, str1, pars);
	else if (format[0] == 'o' || format[0] == 'O')
	{
		while (str1[i] == ' ')
			dst[j++] = str1[i++];
		if (str1[i] != '0' && j > 0)
			dst[j - 1] = '0';
		if (str1[i] != '0' && j == 0)
			dst[j++] = '0';
		while (str1[i])
			dst[j++] = str1[i++];
		dst[j] = '\0';
	}
	free(str1);
	return (dst);
}

void	flags_int(t_pars **pars, char *format, char *str, char *str1)
{
	size_t	i;

	i = 0;
	if ((*pars)->flags & FLAG_NUMBER && (*pars)->flags & FLAG_PRECI && \
			(*pars)->fields > (*pars)->prec)
		str1 = flags_int_1(pars, str, str1, 0);
	if ((*pars)->flags & FLAG_NUMBER && (*pars)->flags & FLAG_PRECI && \
			(*pars)->fields <= (*pars)->prec)
		str1 = flags_int_2(pars, str, str1, 0);
	if (((*pars)->flags & FLAG_NUMBER) == 0 && (*pars)->flags & FLAG_PRECI)
		str1 = flags_int_3(pars, str, str1, 0);
	if (((*pars)->flags & FLAG_NUMBER) && ((*pars)->flags & FLAG_PRECI) == 0)
		str1 = flags_int_4(pars, str, str1, 0);
	if (((*pars)->flags & FLAG_NUMBER) == 0 && ((*pars)->flags & \
				FLAG_PRECI) == 0)
		str1 = flags_int_5(pars, str, str1);
	if ((*pars)->flags & FLAG_DIEZ)
		str1 = func_diez(format, str1, pars, 0);
	if ((*pars)->flags & FLAG_LESS)
		str1 = str_on_left(str1, 0, pars, 0);
	fill_buf(str1, pars, 0);
	free(str);
	free(str1);
}
