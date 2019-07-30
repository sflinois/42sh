/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/03 19:27:38 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/03/06 15:06:24 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	fill_buf1(char *str, t_pars **pars, int size, int i)
{
	while (size > 0)
	{
		if ((*pars)->position + 1 == BUFF_SIZE)
		{
			write(1, (*pars)->buf, (*pars)->position);
			(*pars)->position = 0;
		}
		(*pars)->buf[(*pars)->position++] = str[i++];
		size--;
	}
}

void	fill_buf(char *str, t_pars **pars, int i)
{
	while (str[i])
	{
		if ((*pars)->position + 1 == BUFF_SIZE)
		{
			write(1, (*pars)->buf, (*pars)->position);
			(*pars)->position = 0;
		}
		(*pars)->buf[(*pars)->position] = str[i];
		(*pars)->position++;
		i++;
	}
}

void	clean_all(t_pars **pars)
{
	(*pars)->flags = 0;
	(*pars)->size_str = 0;
	(*pars)->fields = 0;
	(*pars)->prec = 0;
	(*pars)->maj = 0;
	(*pars)->modifier[0] = '\0';
}

void	no_specifier(t_pars **pars, char *format)
{
	char	*str;
	char	*str1;
	int		j;

	j = 0;
	if ((str = ft_strnew(2)) == NULL)
		return ;
	str[0] = format[j++];
	if ((str1 = size_of_malloc(str, pars)) == NULL)
		return ;
	flags_on_str(str1, str, pars, 0);
	free(str);
}

void	fields_for_big_c(t_pars **pars, char *str, int size_c)
{
	char	*str1;
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if ((str1 = (char*)malloc(sizeof(char) * (*pars)->fields + 1)) == NULL)
		return ;
	while (i < ((*pars)->fields - size_c))
	{
		str1[i] = ' ';
		i++;
	}
	while (i < (*pars)->fields)
		str1[i++] = str[j++];
	str1[i] = '\0';
	if ((*pars)->flags & FLAG_LESS)
		str1 = str_on_left(str1, 0, pars, i);
	fill_buf1(str1, pars, i, 0);
	free(str1);
}
