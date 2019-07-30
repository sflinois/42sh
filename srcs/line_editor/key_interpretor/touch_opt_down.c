/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_opt_down.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 16:32:57 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/13 09:54:05 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

void	go_to_the_next_line(t_le *ledit, int nb_co)
{
	int		a;
	int		nb_co_multi;
	int		b;

	b = 0;
	nb_co_multi = nb_co;
	a = ft_strlen(ledit->buffer);
	while (ledit->index_buffer >= nb_co_multi)
		nb_co_multi = nb_co_multi + nb_co;
	if (ledit->index_buffer + ledit->size_prompt <= nb_co)
		nb_co_multi = nb_co_multi - ledit->size_prompt;
	if (nb_co_multi - ledit->index_buffer < a - ledit->index_buffer)
	{
		while (b < nb_co && ledit->index_buffer <= a)
		{
			right_arrow_move_cursor(ledit);
			b++;
		}
	}
}

int		opt_down(t_le *ledit)
{
	int		nb_line;
	int		nb_co;
	int		a;

	a = 0;
	nb_line = tgetnum("li");
	nb_co = tgetnum("co");
	ledit->nb_break_line = 0;
	go_to_the_next_line(ledit, nb_co);
	return (0);
}
