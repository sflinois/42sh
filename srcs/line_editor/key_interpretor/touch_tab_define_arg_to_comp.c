/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_tab_define_arg_to_comp.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 13:53:02 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 17:55:18 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	define_position_cursor(t_le *ledit, char *buff, int i, int *pos)
{
	*pos = 0;
	while (buff[i] && buff[i] == ' ' && i < ledit->index_buffer)
		i++;
	while (buff[i] && i < ledit->index_buffer)
	{
		if (ft_strclen(">< :%#=}", buff[i]) > -1)
		{
			*pos = 1;
		}
		else if (ft_strclen("|&;", buff[i]) > -1)
		{
			i++;
			while (buff[i] && buff[i] == ' ' && i < ledit->index_buffer)
				i++;
			i--;
			*pos = 0;
		}
		else if (buff[i] == '$' && buff[i + 1] && buff[i + 1] == '{')
		{
			i++;
			*pos = 2;
		}
		i++;
	}
}

static int	define_str_to_find(t_le *ledit, char *buff, int i, char **str)
{
	int		size;

	size = 0;
	i = ledit->index_buffer - 1;
	if (i < 0)
		return (-1);
	while (i >= 0 && ft_strclen("|&;>< {:%#", buff[i]) == -1)
		i--;
	i++;
	while (i + size < ledit->index_buffer)
		size++;
	if (size == 0)
		return (-1);
	if ((*str = ft_strsub(buff, i, size, 0)) == NULL)
		return (MALLOC_FAIL);
	return (0);
}

int			define_arg(t_le *ledit, char *buffer, int *pos, char **str)
{
	define_position_cursor(ledit, buffer, 0, pos);
	if ((define_str_to_find(ledit, buffer, 0, str)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (str)
	{
		if ((*str)[0] == '.' || (*str)[0] == '/')
			*pos = 1;
	}
	return (SUCCESS);
}
