/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:24:14 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:40:52 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

static void	move_charac_back_on_buffer(t_le *ledit)
{
	int		b;

	b = ledit->index_buffer - 1;
	while (ledit->buffer[b])
	{
		ledit->buffer[b] = ledit->buffer[b + 1];
		b++;
	}
}

void		delete_charac_on_buffer(t_le *ledit)
{
	int		a;

	a = 0;
	a = ft_strlen(ledit->buffer);
	if (a == ledit->index_buffer)
	{
		ledit->buffer[ledit->index_buffer - 1] = '\0';
	}
	else if (ledit->index_buffer < a)
	{
		move_charac_back_on_buffer(ledit);
	}
}

int			touch_del_character(t_le *ledit)
{
	if (ledit->index_buffer > 0 \
			&& ledit->buffer[ledit->index_buffer - 1] == '\n')
		return (0);
	if (ledit->index_buffer > ledit->limits_back_x)
	{
		left_arrow_move_cursor(ledit);
		ledit->index_buffer++;
		if (ledit->index_buffer > 0)
		{
			ft_tc_clear_after_cursor();
			delete_charac_on_buffer(ledit);
			ledit->index_buffer--;
			ft_tc_save_position_cursor();
			putstr_with_prompt(ledit->i_return, ledit->buffer + ledit->index_buffer);
			ft_tc_restaure_position_cursor();
		}
	}
	return (0);
}
