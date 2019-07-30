/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_to_the_end.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:12:14 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 11:57:38 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "ft_lineedit.h"

static void	index_on_the_next_breakline(t_le *ledit)
{
	while (ledit->buffer[ledit->index_buffer] != '\n')
		ledit->index_buffer++;
	ledit->index_buffer++;
}

void		move_cursor_fifteen_right(void)
{
	int		a;

	a = 11;
	while (a > 0)
	{
		ft_tc_move_cursor_one_right();
		a--;
	}
}

void		down_cursor(t_le *ledit)
{
	while (ledit->buffer[ledit->index_buffer - 1] != '\n' && \
			ledit->index_buffer > 0)
		left_arrow_move_cursor(ledit);
	while (ledit->nb_break_line > 0)
	{
		ft_tc_down_cursor();
		move_cursor_fifteen_right();
		index_on_the_next_breakline(ledit);
		ledit->nb_break_line--;
	}
}

static void	count_nb_break_line(t_le *ledit)
{
	int		a;

	a = ledit->index_buffer;
	while (ledit->buffer[a])
	{
		if (ledit->buffer[a] == '\n')
			ledit->nb_break_line++;
		a++;
	}
}

void		move_cursor_to_the_end(t_le *ledit)
{
	int		b;

	ledit->nb_break_line = 0;
	b = ft_strlen(ledit->buffer);
	if (ledit->index_buffer != b)
	{
		count_nb_break_line(ledit);
		if (ledit->nb_break_line == 0)
		{
			while (ledit->index_buffer < b)
				right_arrow_move_cursor(ledit);
		}
		else
		{
			down_cursor(ledit);
			while (ledit->buffer[ledit->index_buffer])
				right_arrow_move_cursor(ledit);
		}
	}
	else
		return ;
}
