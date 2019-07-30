/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_to_the_start.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 12:17:27 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 11:57:58 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "ft_lineedit.h"

static void	count_nb_breakline_back(t_le *ledit)
{
	int		x;

	x = ledit->index_buffer;
	if (x == (int)ft_strlen(ledit->buffer))
		x--;
	if (x > 0)
	{
		while (x > 0 && ledit->buffer[x])
		{
			if (ledit->buffer[x] == '\n')
				ledit->nb_break_line++;
			x--;
		}
	}
}

static void	back_index_cursor(t_le *ledit)
{
	while (ledit->index_buffer > 0 && \
			ledit->buffer[ledit->index_buffer - 1] != '\n')
		left_arrow_move_cursor(ledit);
}

static void	back_index_to_the_back_breakline(t_le *ledit)
{
	int		x;

	x = ledit->index_buffer;
	ledit->index_buffer = ledit->index_buffer - 2;
	if (ledit->index_buffer < 0)
		ledit->index_buffer = 0;
	else
	{
		while (ledit->buffer[ledit->index_buffer] != '\n' && \
				ledit->index_buffer > 0)
		{
			ledit->index_buffer--;
		}
	}
}

void		up_cursor(t_le *ledit)
{
	while (ledit->nb_break_line > 0)
	{
		ft_tc_up_cursor_one_line();
		back_index_to_the_back_breakline(ledit);
		ledit->nb_break_line--;
	}
}

void		move_cursor_to_the_start(t_le *ledit)
{
	int		b;
	int		x;

	x = ledit->index_buffer;
	b = ft_strlen(ledit->buffer);
	if (ledit->index_buffer > 0)
	{
		ledit->nb_break_line = 0;
		count_nb_breakline_back(ledit);
		back_index_cursor(ledit);
		if (ledit->nb_break_line > 0)
			up_cursor(ledit);
	}
	ft_tc_clear_after_cursor();
}
