/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_shift_and_arrow.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 11:29:51 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:40:42 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

static void	select_mode_on_the_right(t_le *ledit)
{
	int		b;
	int		x;

	x = ledit->index_buffer;
	b = ledit->copy_index;
	while (x < b)
	{
		ft_putchar(ledit->buffer[x]);
		x++;
	}
}

void		select_sens_select(t_le *ledit, int left_right)
{
	if (left_right == 0)
	{
		if (ledit->sens_select == 2)
			rewrite_buffer(ledit);
		if (ledit->sens_select == 0)
			ledit->sens_select = 1;
	}
	else
	{
		if (ledit->sens_select == 1)
			rewrite_buffer(ledit);
		if (ledit->sens_select == 0)
			ledit->sens_select = 2;
	}
	if (ledit->save_index_select == 0)
	{
		ledit->copy_index = ledit->index_buffer;
		ledit->save_index_select = 1;
	}
}

int			touch_shift_left_arrow(t_le *ledit)
{
	int		b;

	b = 0;
	select_sens_select(ledit, 0);
	recup_the_limits_back(ledit);
	if (ledit->limits_back_x >= ledit->index_buffer)
		return (0);
	else
	{
		left_arrow_move_cursor(ledit);
		ft_tc_save_position_cursor();
		ft_tc_clear_after_cursor();
		ft_tc_select_mode();
		select_mode_on_the_right(ledit);
		ft_tc_end_select_mode();
		putstr_with_prompt(ledit->i_return, ledit->buffer + ledit->copy_index);
		ft_tc_restaure_position_cursor();
	}
	return (0);
}

int			touch_shift_right_arrow(t_le *ledit)
{
	int		b;

	b = ft_strlen(ledit->buffer) - 1;
	select_sens_select(ledit, 1);
	if (ledit->index_buffer >= b)
		return (0);
	else
	{
		ft_tc_save_position_cursor();
		ft_tc_clear_after_cursor();
		ft_tc_select_mode();
		ft_putchar(ledit->buffer[ledit->index_buffer]);
		ft_tc_end_select_mode();
		putstr_with_prompt(ledit->i_return, ledit->buffer + ledit->index_buffer + 1);
		ft_tc_restaure_position_cursor();
		right_arrow_move_cursor(ledit);
	}
	return (0);
}
