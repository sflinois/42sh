/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DOU_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/09 13:35:36 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/04 18:53:10 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int		dou_arg(t_pars **pars, char *format, va_list ap, int i)
{
	i = 0;
	(*pars)->modifier[0] = 'M';
	if (format[0] == 'D')
		signed_conv(pars, format, ap, 0);
	if (format[0] == 'O' || format[0] == 'U')
		unsigned_conv(pars, format, ap, 0);
	return (0);
}

void	active_flag(t_pars **pars)
{
	if (((*pars)->flags & FLAG_DIEZ) == 0)
		(*pars)->flags = (*pars)->flags + FLAG_DIEZ;
	if ((*pars)->flags & FLAG_ADD)
		(*pars)->flags = (*pars)->flags - FLAG_ADD;
	if ((*pars)->flags & FLAG_SPACE)
		(*pars)->flags = (*pars)->flags - FLAG_SPACE;
}

int		p_arg(t_pars **pars, char *format, va_list ap, int size)
{
	char	str[33];
	char	*str1;
	char	*str2;
	void	*addr;

	addr = va_arg(ap, void*);
	ft_bzero(str, 33);
	ft_utoa_base((unsigned long long int)addr, 16, 0, str);
	if (addr == 0 && (*pars)->flags & FLAG_PRECI && (*pars)->prec == 0)
		str[0] = '\0';
	size = ft_strlen(str);
	if (size < 2 && (*pars)->flags & FLAG_NUMBER && ((*pars)->flags & \
				FLAG_PRECI) == 0 && (*pars)->flags & FLAG_ZERO)
		size = 3;
	(*pars)->size_str = size;
	if ((str1 = ft_strnew(size + 1)) == NULL)
		return (0);
	size = bigger_size(size, pars);
	str1 = ft_reverse(str, str1, pars, 0);
	if ((str2 = ft_strnew(size + 1)) == NULL)
		return (0);
	active_flag(pars);
	flags_int(pars, format, str1, str2);
	(*pars)->flags = 0;
	return (0);
}

char	*per_arg2(t_pars **pars, char *str2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (i < (*pars)->fields - 1 && ((*pars)->flags & \
				FLAG_ZERO) == 0)
		str2[i++] = ' ';
	while (i < (*pars)->fields - 1 && (*pars)->flags & FLAG_ZERO)
		str2[i++] = '0';
	str2[i++] = '%';
	str2[i] = '\0';
	return (str2);
}

int		per_arg(t_pars **pars, char *format, va_list ap, int i)
{
	char	*str1;
	char	*str2;

	(void)ap;
	(void)format;
	if ((str1 = ft_strnew(2)) == NULL)
		return (0);
	str1[i++] = '%';
	str1[i] = '\0';
	if ((*pars)->flags & FLAG_NUMBER)
	{
		if ((str2 = ft_strnew((*pars)->fields + 1)) == NULL)
			return (0);
		str2 = per_arg2(pars, str2);
		if ((*pars)->flags & FLAG_LESS)
			str2 = str_on_left(str2, 0, pars, 0);
		fill_buf(str2, pars, 0);
		free(str2);
	}
	else
		fill_buf(str1, pars, 0);
	free(str1);
	return (0);
}
