/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_character.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 10:39:10 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:40:27 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include <term.h>

static void	stock_character_on_buffer(t_le *ledit, char *buf)
{
	ledit->buffer[ledit->index_buffer] = buf[0];
	ledit->index_buffer++;
}

static void	move_line_right(t_le *ledit, char buf)
{
	int		b;

	b = ft_strlen(ledit->buffer) - 1;
	while (b >= ledit->index_buffer)
	{
		ledit->buffer[b + 1] = ledit->buffer[b];
		b--;
	}
	b++;
	ledit->buffer[b] = buf;
	putstr_with_prompt(ledit->i_return, ledit->buffer + b);
}

static void	inser_character(t_le *ledit, char buf)
{
	ft_tc_save_position_cursor();
	ft_tc_clear_after_cursor();
	move_line_right(ledit, buf);
	ft_tc_restaure_position_cursor();
	right_arrow_move_cursor(ledit);
}

int			print_character(t_le *ledit, char *buf)
{
	if (ft_strlen(ledit->buffer) > 520)
		return (0);
	if (ledit->index_buffer < (int)ft_strlen(ledit->buffer))
		inser_character(ledit, buf[0]);
	else
	{
		stock_character_on_buffer(ledit, buf);
		ft_putchar(buf[0]);
	}
	if (buf[0] == '\n')
	{
		ledit->nb_break_line++;
		ledit->limits_back_x = ledit->index_buffer;
	}
	return (0);
}
