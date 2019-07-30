/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_opt_and_arrow.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 17:18:24 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/12 18:22:22 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

int		opt_left(t_le *ledit)
{
	int		b;
	int		c;

	c = 0;
	b = ledit->index_buffer - 1;
	if ((c = check_if_line_break(ledit)) > 0)
		ledit->limits_back_x = c + 1;
	if (b == 0)
		return (0);
	while (b > 0 && ledit->buffer[b] != ' ')
		b--;
	while (ledit->buffer[b] == ' ')
		b--;
	while (ledit->index_buffer > ledit->limits_back_x && \
			ledit->index_buffer > b)
		left_arrow_move_cursor(ledit);
	return (0);
}

int		opt_right(t_le *ledit)
{
	int		b;
	int		c;

	c = ft_strlen(ledit->buffer);
	b = ledit->index_buffer;
	if (b == c)
		return (0);
	while (b < c && ledit->buffer[b] != ' ' && ledit->buffer[b] != '\n')
		b++;
	while (ledit->buffer[b] == ' ')
		b++;
	while (ledit->index_buffer < b)
		right_arrow_move_cursor(ledit);
	return (0);
}
