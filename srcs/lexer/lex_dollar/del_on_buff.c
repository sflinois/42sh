/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_on_buff.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:53:16 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:07:57 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

void	cut_expansion_dollar(t_le *ledit, int *i)
{
	ledit->index_buffer = (*i);
	while ((*i) > ledit->start_cut)
	{
		del_on_buffer(ledit);
		(*i)--;
	}
}

int		del_on_buffer(t_le *ledit)
{
	if (ledit->index_buffer > 0 \
			&& ledit->buffer[ledit->index_buffer - 1] == '\n')
		return (0);
	if (ledit->index_buffer > ledit->limits_back_x)
	{
		if (ledit->index_buffer > 0)
		{
			delete_charac_on_buffer(ledit);
			ledit->index_buffer--;
		}
	}
	return (0);
}
