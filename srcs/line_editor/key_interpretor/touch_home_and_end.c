/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_home_and_end.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 09:59:38 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 16:11:18 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

void	recup_the_limits_back(t_le *ledit)
{
	int		a;

	a = check_if_line_break(ledit);
	if (a > 0)
		ledit->limits_back_x = a + 1;
	else
		ledit->limits_back_x = 0;
}

int		touch_end(t_le *ledit)
{
	int		a;

	a = ft_strlen(ledit->buffer);
	recup_the_limits_back(ledit);
	if (ledit->index_buffer < a)
	{
		while (ledit->index_buffer < a && \
				ledit->buffer[ledit->index_buffer] != '\n')
			right_arrow_move_cursor(ledit);
	}
	return (0);
}

int		touch_home(t_le *ledit)
{
	recup_the_limits_back(ledit);
	while (ledit->index_buffer > ledit->limits_back_x)
		left_arrow_move_cursor(ledit);
	return (0);
}
