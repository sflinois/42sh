/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_on_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 16:35:29 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/04 18:21:20 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*flags_int_1_2(t_pars **pars, char *str, char *str1)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((*pars)->flags & FLAG_SIGN)
		(*pars)->fields++;
	if ((*pars)->size_str < (*pars)->fields)
	{
		while (i < ((*pars)->fields - (*pars)->size_str))
			str1[i++] = ' ';
	}
	if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
	{
		str1[i++] = (*pars)->sign;
		(*pars)->fields++;
	}
	while (str[j])
		str1[i++] = str[j++];
	str1[i] = '\0';
	return (str1);
}

char	*flags_int_1_1(t_pars **pars, char *str, char *str1)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if ((*pars)->flags & FLAG_SPACE)
		str1[i++] = ' ';
	if ((*pars)->flags & FLAG_ZERO && (*pars)->prec == (*pars)->size_str)
	{
		if ((*pars)->flags & FLAG_SIGN || (*pars)->flags & FLAG_ADD)
		{
			str1[i++] = (*pars)->sign;
			(*pars)->fields++;
			if ((*pars)->flags & FLAG_SIGN)
				(*pars)->fields++;
		}
		while (i < ((*pars)->fields - (*pars)->size_str))
			str1[i++] = '0';
		while (str[j])
			str1[i++] = str[j++];
		str1[i] = '\0';
	}
	else if ((*pars)->prec <= (*pars)->size_str)
		str1 = flags_int_1_2(pars, str, str1);
	return (str1);
}

char	*flags_int_1(t_pars **pars, char *str, char *str1, size_t i)
{
	size_t	j;

	j = 0;
	if ((*pars)->prec > (*pars)->size_str)
	{
		if ((*pars)->flags & FLAG_SPACE)
			str1[i++] = ' ';
		while (i < ((*pars)->fields - (*pars)->prec))
			str1[i++] = ' ';
		if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
		{
			str1[i++] = (*pars)->sign;
			(*pars)->fields++;
			if ((*pars)->flags & FLAG_SIGN)
				(*pars)->fields++;
		}
		while (i < ((*pars)->fields - (*pars)->size_str))
			str1[i++] = '0';
		while (str[j])
			str1[i++] = str[j++];
		str1[i] = '\0';
	}
	else if ((*pars)->prec <= (*pars)->size_str || (*pars)->flags & FLAG_ZERO)
		str1 = flags_int_1_1(pars, str, str1);
	return (str1);
}

char	*flags_int_2_1(t_pars **pars, char *str, char *str1, size_t i)
{
	size_t	j;

	j = 0;
	if ((*pars)->flags & FLAG_ZERO && (*pars)->fields == (*pars)->prec && \
			((*pars)->flags & FLAG_SIGN || (*pars)->flags & FLAG_ADD))
	{
		if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
		{
			str1[i++] = (*pars)->sign;
			(*pars)->fields = (*pars)->fields + 2;
		}
		while (i < (*pars)->fields - (*pars)->prec)
			str1[i++] = '0';
		while (str[j])
			str1[i++] = str[j++];
		return (str1);
	}
	if ((*pars)->flags & FLAG_ADD || (*pars)->flags & FLAG_SIGN)
		str1[i++] = (*pars)->sign;
	if ((*pars)->flags & FLAG_SPACE)
		str1[i++] = ' ';
	while (str[j])
		str1[i++] = str[j++];
	str1[i] = '\0';
	return (str1);
}

char	*flags_int_2(t_pars **pars, char *str, char *str1, size_t i)
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
				(*pars)->prec = (*pars)->prec + 1;
		}
		if ((*pars)->flags & FLAG_SPACE)
		{
			str1[i++] = ' ';
			(*pars)->prec++;
		}
		while (i < (*pars)->prec - (*pars)->size_str)
			str1[i++] = '0';
		while (i < (*pars)->prec)
			str1[i++] = str[j++];
	}
	if ((*pars)->prec <= (*pars)->size_str)
		str1 = flags_int_2_1(pars, str, str1, 0);
	return (str1);
}
