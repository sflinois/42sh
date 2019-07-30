/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inser_on_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:10:37 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:32:19 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static void	add_char(t_le *ledit, char *buf)
{
	ledit->buffer[ledit->index_buffer] = buf[0];
}

static void	inser_char(t_le *ledit, char buf)
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
}

void		inser_on_buffer(t_le *ledit, char *buf)
{
	if (ledit->index_buffer < (int)ft_strlen(ledit->buffer))
		inser_char(ledit, buf[0]);
	else
		add_char(ledit, buf);
	ledit->index_buffer++;
}
