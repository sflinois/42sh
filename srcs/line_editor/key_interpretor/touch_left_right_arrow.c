/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_left_right_arrow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 15:27:31 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 11:45:54 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

int			index_first_col(t_le *ledit)
{
	int		nb_co;
	int		i;

	i = 0;
	nb_co = tgetnum("co");
	if (((ledit->index_buffer + ledit->size_prompt) % nb_co) == 0)
	{
		ft_tc_up_cursor_one_line();
		ledit->index_buffer -= nb_co;
		while (i < nb_co - 1)
		{
			right_arrow_move_cursor(ledit);
			i++;
		}
		return (0);
	}
	return (1);
}

int			left_arrow_move_cursor(t_le *ledit)
{
	if (index_first_col(ledit) == 0)
		return (0);
	if (ledit->index_buffer > ledit->limits_back_x)
	{
		ledit->index_buffer--;
		ft_tc_move_cursor_left();
	}
	return (0);
}

static int	index_on_the_last_co(t_le *ledit)
{
	int		nb_co;
	int		nb_co_multi;

	nb_co = tgetnum("co");
	nb_co_multi = nb_co;
	while (ledit->index_buffer > nb_co_multi)
		nb_co_multi = nb_co_multi + nb_co;
	nb_co_multi = nb_co_multi - ledit->size_prompt;
	nb_co_multi -= 1;
	if (ledit->index_buffer == nb_co_multi && (int)ft_strlen(ledit->buffer) > \
			ledit->index_buffer)
	{
		ft_tc_down_cursor();
		ledit->index_buffer++;
		return (1);
	}
	return (0);
}

int			right_arrow_move_cursor(t_le *ledit)
{
	if (index_on_the_last_co(ledit) == 1)
		return (0);
	else if (ledit->buffer[ledit->index_buffer] != '\n' && \
			ledit->index_buffer < (int)ft_strlen(ledit->buffer))
	{
		ledit->index_buffer++;
		ft_tc_move_cursor_one_right();
	}
	return (0);
}
