/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_on_int2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 20:02:35 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/04 18:29:48 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*flags_int_3_1(t_pars **pars, char *str, char *str1)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
	{
		str1[i++] = (*pars)->sign;
		(*pars)->flags++;
	}
	if ((*pars)->flags & FLAG_SPACE)
		str1[i++] = ' ';
	while (str[j])
		str1[i++] = str[j++];
	str1[i] = '\0';
	return (str1);
}

char	*flags_int_3(t_pars **pars, char *str, char *str1, size_t i)
{
	size_t	j;

	j = 0;
	if ((*pars)->prec > (*pars)->size_str)
	{
		if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
		{
			str1[i++] = (*pars)->sign;
			(*pars)->prec++;
			if ((*pars)->flags & FLAG_SIGN)
				(*pars)->size_str--;
		}
		if ((*pars)->flags & FLAG_SPACE)
		{
			(*pars)->prec++;
			str1[i++] = ' ';
		}
		while (i < ((*pars)->prec - (*pars)->size_str))
			str1[i++] = '0';
		while (str[j])
			str1[i++] = str[j++];
	}
	if ((*pars)->prec <= (*pars)->size_str)
		str1 = flags_int_3_1(pars, str, str1);
	return (str1);
}

char	*flags_int_4_1(t_pars **pars, char *str, char *str1, size_t i)
{
	size_t	j;

	j = 0;
	if ((*pars)->flags & FLAG_SIGN)
		(*pars)->fields++;
	if ((*pars)->fields > (*pars)->size_str)
	{
		while (i < (*pars)->fields - (*pars)->size_str)
			str1[i++] = ' ';
		if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
			str1[i++] = (*pars)->sign;
		while (str[j])
			str1[i++] = str[j++];
	}
	if ((*pars)->fields <= (*pars)->size_str)
	{
		if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
			str1[i++] = (*pars)->sign;
		if ((*pars)->flags & FLAG_SPACE)
			str1[i++] = ' ';
		while (str[j])
			str1[i++] = str[j++];
	}
	str1[i] = '\0';
	return (str1);
}

char	*flags_int_4(t_pars **pars, char *str, char *str1, size_t i)
{
	size_t	j;

	j = 0;
	if ((*pars)->fields > (*pars)->size_str && (*pars)->flags & FLAG_ZERO)
	{
		if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
		{
			str1[i++] = (*pars)->sign;
			(*pars)->fields++;
			if ((*pars)->flags & FLAG_SIGN)
				(*pars)->size_str--;
		}
		if ((*pars)->flags & FLAG_SPACE)
			str1[i++] = ' ';
		while (i < (*pars)->fields - (*pars)->size_str)
			str1[i++] = '0';
		while (str[j])
			str1[i++] = str[j++];
		str1[i] = '\0';
	}
	else
		str1 = flags_int_4_1(pars, str, str1, 0);
	return (str1);
}

char	*flags_int_5(t_pars **pars, char *str, char *str1)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
		str1[i++] = (*pars)->sign;
	if ((*pars)->flags & FLAG_SPACE)
		str1[i++] = ' ';
	while (str[j])
	{
		str1[i++] = str[j++];
	}
	str1[i] = '\0';
	return (str1);
}
