/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_copy_and_paste.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 10:23:51 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/31 14:25:47 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

int		copy_select_char(t_le *ledit)
{
	int		x;
	int		b;

	x = ledit->index_buffer;
	b = ledit->copy_index;
	if (ledit->sens_select == 1)
	{
		if ((ledit->str_opt_c = ft_strndup(ledit->buffer + x, b - x)) == NULL)
			return (MALLOC_FAIL);
	}
	if (ledit->sens_select == 2)
	{
		if ((ledit->str_opt_c = ft_strndup(ledit->buffer + b, x - b)) == NULL)
			return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

int		touch_copy(t_le *ledit)
{
	if (ledit->str_opt_c != NULL)
	{
		free(ledit->str_opt_c);
		ledit->str_opt_c = NULL;
	}
	if (ledit->str_opt_c == NULL)
	{
		copy_select_char(ledit);
		rewrite_buffer(ledit);
	}
	return (SUCCESS);
}

int		touch_paste(t_le *ledit)
{
	int		b;

	b = 0;
	if (ledit->str_opt_c)
	{
		while (ledit->str_opt_c[b])
		{
			print_character(ledit, ledit->str_opt_c + b);
			b++;
		}
		free(ledit->str_opt_c);
		ledit->str_opt_c = NULL;
	}
	return (SUCCESS);
}
