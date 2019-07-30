/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_on_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 13:15:19 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/06 14:50:28 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*flags_on_str1(char *str, char *str1, t_pars **pars, size_t i)
{
	size_t	j;

	j = 0;
	if ((*pars)->fields <= ft_strlen(str1))
		while (j < (*pars)->prec && str1[j])
		{
			str[j] = str1[j];
			j++;
		}
	if ((*pars)->fields > ft_strlen(str1))
	{
		while (j < (*pars)->fields - ft_strlen(str1))
		{
			str[j] = ' ';
			j++;
		}
		while ((i + j) < (*pars)->fields)
		{
			str[j + i] = str1[i];
			i++;
		}
	}
	return (str);
}

char	*flags_on_str2_1(t_pars **pars, char *str, char *str1)
{
	size_t	j;
	size_t	i;

	i = 0;
	j = -1;
	if ((*pars)->flags & FLAG_ZERO)
		while (i < (*pars)->fields - (*pars)->prec)
			str[i++] = '0';
	while (i < (*pars)->fields - ((*pars)->prec))
		str[i++] = ' ';
	while (++j < (*pars)->prec)
		str[i + j] = str1[j];
	return (str);
}

char	*flags_on_str2(char *str, char *str1, t_pars **pars, size_t i)
{
	size_t	j;

	j = -1;
	if ((*pars)->prec > ft_strlen(str1))
	{
		j = 0;
		if ((*pars)->flags & FLAG_ZERO)
			while (i < (*pars)->fields - ft_strlen(str1))
				str[i++] = '0';
		while (i < (*pars)->fields - ft_strlen(str1))
			str[i++] = ' ';
		while (i + j < (*pars)->fields)
		{
			str[i + j] = str1[j];
			j++;
		}
	}
	else if ((*pars)->prec <= ft_strlen(str1))
		str = flags_on_str2_1(pars, str, str1);
	return (str);
}

char	*flags_on_str3(char *str, char *str1, t_pars **pars, size_t i)
{
	if ((*pars)->prec >= ft_strlen(str1))
		while (str1[i])
		{
			str[i] = str1[i];
			i++;
		}
	else if ((*pars)->prec < ft_strlen(str1))
		while (i < (*pars)->prec && str1[i])
		{
			str[i] = str1[i];
			i++;
		}
	return (str);
}

char	*flags_on_str4(char *str, char *str1, t_pars **pars, size_t i)
{
	int		j;

	j = 0;
	if ((*pars)->fields <= ft_strlen(str1))
		while (str1[i])
		{
			str[i] = str1[i];
			i++;
		}
	else if ((*pars)->fields > ft_strlen(str1))
	{
		if ((*pars)->flags & FLAG_ZERO)
			while (i < (*pars)->fields - (ft_strlen(str1)))
				str[i++] = '0';
		while (i < (*pars)->fields - (ft_strlen(str1)))
			str[i++] = ' ';
		while (j + i < (*pars)->fields)
		{
			str[i + j] = str1[j];
			j++;
		}
	}
	return (str);
}
