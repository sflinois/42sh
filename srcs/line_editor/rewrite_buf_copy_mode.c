/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rewrite_buf_copy_mode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:21:30 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:39:58 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "ft_minishell.h"

void	rewrite_buffer(t_le *ledit)
{
	int		x;

	x = ledit->index_buffer;
	ft_tc_save_position_cursor();
	move_cursor_to_the_start(ledit);
	putstr_with_prompt(ledit->i_return, ledit->buffer);
	ledit->index_buffer = x;
	ft_tc_restaure_position_cursor();
	ledit->sens_select = 0;
	ledit->save_index_select = 0;
}

int		check_mode_copy(t_le *ledit, char *buf)
{
	int		x;

	x = ledit->index_buffer;
	if (ledit->save_index_select != 1 && buf[0] == -61 && buf[1] == -89)
		return (1);
	else if (ledit->save_index_select != 1)
		return (0);
	if (ledit->save_index_select == 1 && buf[0] == -61 && buf[1] == -89)
	{
		touch_copy(ledit);
		rewrite_buffer(ledit);
		return (1);
	}
	else if ((buf[0] != 27 || buf[1] != 91 || buf[2] != 49 || buf[3] != 59 || \
			buf[4] != 50) && (ledit->save_index_select == 1))
		rewrite_buffer(ledit);
	return (0);
}
