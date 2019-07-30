/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_opt_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/24 15:26:58 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/13 09:52:23 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

int		check_if_line_break(t_le *ledit)
{
	int		b;

	b = ledit->index_buffer - 1;
	if (b > 0)
	{
		while (b > 0)
		{
			if (ledit->buffer[b] == '\n')
				return (b);
			b--;
		}
	}
	else
		return (-1);
	return (0);
}

void	back_nb_col(t_le *ledit, int nb_co)
{
	int		nb_co_multi;
	int		i;

	i = 0;
	nb_co_multi = nb_co;
	while (nb_co_multi <= (ledit->index_buffer + ledit->size_prompt))
		nb_co_multi += nb_co;
	if (nb_co_multi > (ledit->index_buffer + ledit->size_prompt))
	{
		while (i < nb_co && ledit->index_buffer > 0)
		{
			left_arrow_move_cursor(ledit);
			i++;
		}
	}
}

int		opt_up(t_le *ledit)
{
	int		a;
	int		nb_line;
	int		nb_co;

	nb_line = tgetnum("li");
	nb_co = tgetnum("co");
	a = check_if_line_break(ledit);
	if (a == -1)
		return (0);
	else if (a == 0)
	{
		back_nb_col(ledit, nb_co);
	}
	return (0);
}
