/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_backslashn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 16:47:29 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 11:59:33 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "ft_lineedit.h"

static void	replace_backslashn(char *buffer)
{
	int		i;

	i = 0;
	if (!buffer)
		return ;
	while (buffer[i])
	{
		if (buffer[i] == find_char_in_str(buffer[i], "\"'"))
		{
			i++;
			if (buffer[i] && buffer[i] == '\n')
				echap_charac(buffer, i);
		}
		if (buffer[i] == '\\' && buffer[i + 1] && buffer[i + 1] == '\n')
		{
			echap_charac(buffer, i);
			echap_charac(buffer, i);
		}
		if (buffer[i] == '\n')
			buffer[i] = ' ';
		else
			i++;
	}
}

int			buffer_in_one_line(char *str)
{
	int		i;

	i = 0;
	replace_backslashn(str);
	while (str[i])
	{
		if (str[i] == ' ')
		{
			i++;
			while (str[i] && str[i] == ' ')
				echap_charac(str, i);
		}
		if (str[i])
			i++;
	}
	return (SUCCESS);
}
