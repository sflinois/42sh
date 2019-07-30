/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ws_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:14:20 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/06 13:35:27 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*fields_on_s(t_pars **pars, char *str, int size_c)
{
	char	*dst;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((dst = ft_strnew((*pars)->fields + 1)) == NULL)
		return (0);
	if ((*pars)->flags & FLAG_ZERO)
		while (i < (*pars)->fields - size_c)
			dst[i++] = '0';
	while (i < (*pars)->fields - size_c)
		dst[i++] = ' ';
	while (str[j])
		dst[i++] = str[j++];
	dst[i] = '\0';
	if ((*pars)->flags & FLAG_LESS)
		dst = str_on_left(dst, 0, pars, 0);
	free(str);
	return (dst);
}

char	*cut_s(t_pars **pars, char *str1, wchar_t *str, size_t i)
{
	size_t	j;
	int		x;

	x = 0;
	j = 0;
	while (str[x] && j <= (*pars)->prec)
	{
		i = bites_in_char(str[x++]);
		j = j + i;
	}
	if (j > (*pars)->prec)
		j = j - i;
	str1[j] = '\0';
	return (str1);
}

char	*ws_arg1(t_pars **pars)
{
	char	*str1;
	size_t	i;

	i = 6;
	if ((str1 = ft_strdup("(null)")) == NULL)
		return (0);
	if ((*pars)->flags & FLAG_PRECI && (*pars)->prec < i)
	{
		str1[(*pars)->prec] = '\0';
		i = ft_strlen(str1);
	}
	if ((*pars)->flags & FLAG_NUMBER && (*pars)->fields > i)
		str1 = fields_on_s(pars, str1, i);
	return (str1);
}

char	*ws_arg2(t_pars **pars, wchar_t *str, char *str1)
{
	size_t	a;
	int		i;
	int		j;

	i = 0;
	j = 0;
	a = ft_wstrlen(str);
	if ((str1 = ft_strnew((a * 4) + 1)) == NULL)
		return (0);
	while (str[j])
	{
		fill_char(str[j], str1, &i);
		j++;
	}
	str1[i] = '\0';
	if ((*pars)->flags & FLAG_PRECI && (*pars)->prec < (size_t)i)
	{
		str1 = cut_s(pars, str1, str, 0);
		i = ft_strlen(str1);
	}
	if ((*pars)->flags & FLAG_NUMBER && (*pars)->fields > (size_t)i)
		str1 = fields_on_s(pars, str1, i);
	return (str1);
}

int		ws_arg(t_pars **pars, char *format, va_list ap, int i)
{
	wchar_t		*str;
	char		*str1;
	size_t		a;

	i = 0;
	(void)format;
	str = va_arg(ap, wchar_t *);
	str1 = NULL;
	if (str == NULL)
	{
		str1 = ws_arg1(pars);
	}
	else
	{
		str1 = ws_arg2(pars, str, str1);
	}
	a = ft_strlen(str1);
	fill_buf1(str1, pars, a, 0);
	free(str1);
	return (0);
}
