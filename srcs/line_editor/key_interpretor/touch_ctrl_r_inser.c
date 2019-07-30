/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_ctrl_r_inser.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:05:39 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 11:43:54 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

int		inser_char_buf_search(char *buffer, int *index, char *inser)
{
	int		nb_co;
	int		nb_co_multi;

	nb_co = tgetnum("co");
	nb_co_multi = nb_co;
	buffer[*index] = inser[0];
	while (*index > nb_co_multi)
		nb_co_multi = nb_co_multi + nb_co;
	nb_co_multi = nb_co_multi - ft_strlen("(reverse-i-search) : ");
	nb_co_multi -= 1;
	if (*index == nb_co_multi && (int)ft_strlen(buffer) > *index)
	{
		ft_tc_down_cursor();
		(*index)++;
		ft_putchar(inser[0]);
	}
	else
	{
		(*index)++;
		ft_putchar(inser[0]);
	}
	return (0);
}

int		touch_del_buf_search(char *buffer, int *index, int i, int nb_co)
{
	if (*index == 0)
		return (0);
	ft_tc_move_cursor_left();
	ft_tc_del_the_carac();
	if ((((*index) + (int)ft_strlen("(reverse-i-search) : ")) % nb_co) == 0)
	{
		(*index)--;
		buffer[*index] = '\0';
		ft_tc_up_cursor_one_line();
		(*index) -= nb_co;
		while (i < nb_co)
		{
			ft_tc_move_cursor_one_right();
			(*index)++;
			i++;
		}
	}
	else
	{
		(*index)--;
		buffer[*index] = '\0';
	}
	return (0);
}
