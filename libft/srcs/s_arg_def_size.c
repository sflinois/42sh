/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_arg.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 15:13:09 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/06 14:51:51 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		bigger_size_int(size_t size, t_pars **pars)
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
	{
		if ((*pars)->prec >= size)
			return ((*pars)->prec);
		return (size);
	}
	if ((*pars)->flags & FLAG_PRECI && (*pars)->flags & FLAG_NUMBER && \
			size >= (*pars)->prec && size >= (*pars)->fields)
		return (size);
	if ((*pars)->prec >= size && (*pars)->prec >= (*pars)->fields)
		return ((*pars)->prec);
	if ((*pars)->fields > size)
		return ((*pars)->fields);
	return (0);
}

char	*str_on_left2(char *str1, char *str2, t_pars **pars, int size)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str1[i] == ' ' && str1[i])
		i++;
	if ((*pars)->flags & FLAG_SPACE)
	{
		str2[j++] = ' ';
		i--;
	}
	while (j + i < size)
	{
		str2[j] = str1[i + j];
		j++;
	}
	while (i > 0)
	{
		str2[j++] = ' ';
		i--;
	}
	str2[j] = '\0';
	return (str2);
}

char	*str_on_left(char *str1, int i, t_pars **pars, int x)
{
	char	*str2;
	int		size;

	if (x > 0)
		size = x;
	else
		size = ft_strlen(str1);
	if ((str2 = ft_strnew(size + 1)) == NULL)
		return (0);
	if (str1[i] && str1[i] == ' ')
	{
		str2 = str_on_left2(str1, str2, pars, size);
		free(str1);
		return (str2);
	}
	free(str2);
	return (str1);
}

void	flags_on_str(char *str, char *str1, t_pars **pars, size_t i)
{
	int		j;

	j = -1;
	if ((*pars)->flags & FLAG_NUMBER && (*pars)->flags & FLAG_PRECI && \
			(*pars)->fields > (*pars)->prec)
		str = flags_on_str2(str, str1, pars, 0);
	if ((*pars)->flags & FLAG_NUMBER && (*pars)->flags & FLAG_PRECI && \
			(*pars)->fields <= (*pars)->prec)
		str = flags_on_str1(str, str1, pars, 0);
	if (((*pars)->flags & FLAG_NUMBER) == 0 && (*pars)->flags & FLAG_PRECI)
		str = flags_on_str3(str, str1, pars, 0);
	if (((*pars)->flags & FLAG_NUMBER) && ((*pars)->flags & FLAG_PRECI) == 0)
		str = flags_on_str4(str, str1, pars, 0);
	if (((*pars)->flags & FLAG_NUMBER) == 0 && ((*pars)->flags & \
				FLAG_PRECI) == 0)
		while (str1[i])
		{
			str[i] = str1[i];
			i++;
		}
	if ((*pars)->flags & FLAG_LESS)
		str = str_on_left(str, 0, pars, 0);
	fill_buf(str, pars, 0);
	free(str);
}

int		s_arg(t_pars **pars, char *format, va_list ap, int i)
{
	char	*str;
	char	*str1;

	i = 0;
	if ((*pars)->modifier[0] == 'l')
	{
		ws_arg(pars, format, ap, 0);
		return (0);
	}
	str1 = va_arg(ap, char *);
	if (str1 == NULL)
		str1 = "(null)";
	if ((str = size_of_malloc(str1, pars)) == NULL)
		return (0);
	flags_on_str(str, str1, pars, 0);
	return (0);
}
