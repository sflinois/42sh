/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 16:58:23 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/04 14:21:22 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <stdint.h>
#include <wchar.h>

char	*ft_reverse(char *str, char *str1, t_pars **pars, int i)
{
	int		j;

	j = 0;
	while (str[i])
		i++;
	if (i > 0 && str[i - 1] == '-')
	{
		i--;
		(*pars)->sign = '-';
		(*pars)->flags = (*pars)->flags | FLAG_SIGN;
		if ((*pars)->flags & FLAG_SPACE)
			(*pars)->flags = (*pars)->flags - FLAG_SPACE;
		(*pars)->fields--;
	}
	else
	{
		(*pars)->sign = '+';
		if ((*pars)->flags & FLAG_ADD)
			(*pars)->fields--;
	}
	while (i > 0)
		str1[j++] = str[--i];
	str1[j] = '\0';
	return (str1);
}

char	*ft_itoa_base(long long int value, int base, int i, char *str)
{
	long long int		a;
	int					neg;
	int					max;

	max = 0;
	a = 0;
	neg = value < 0 ? -1 : 1;
	value *= neg;
	if (value < 0)
	{
		value += 1;
		value *= -1;
		max = 1;
	}
	if (value == 0)
		str[i++] = '0';
	while (value > 0)
	{
		str[i++] = max == 1 ? '0' + (value % base + 1) : '0' + (value % base);
		max = 0;
		value = value / base;
	}
	str[i] = neg < 0 ? '-' : '\0';
	str[i + 1] = '\0';
	return (str);
}

char	*ft_utoa_base(unsigned long long int value, int base, \
		int maj, char *str)
{
	int		i;
	int		a;

	a = 0;
	i = 0;
	maj = maj == 1 ? 'a' - 'A' : 0;
	if (value == 0)
		str[i++] = '0';
	while (value > 0)
	{
		a = value % base;
		str[i] = a > 9 ? 'a' + a - maj - 10 : '0' + a;
		value = value / base;
		i++;
	}
	str[i] = '\0';
	return (str);
}
