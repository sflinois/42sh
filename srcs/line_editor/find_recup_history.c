/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_recup_history.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:09:06 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 15:49:16 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static int	recup_command_nb_inverse(t_le *ledit, int i, int nb_del)
{
	int		j;
	int		x;

	if (ledit->buffer[i] == '\0')
		return (unexpected_token("newline"));
	if ((j = protect_atoi(ledit->buffer + (i), 0)) < 0)
		return (unexpected_token("newline"));
	x = j;
	while (x > 9)
	{
		nb_del++;
		x = x / 10;
	}
	nb_del++;
	while (ledit->index_buffer > i + nb_del)
		left_arrow_move_cursor(ledit);
	while (nb_del + 2 > 0)
	{
		nb_del--;
		touch_del_character(ledit);
	}
	if ((copy_line_hist_back(&ledit->list_histo, ledit, j)) == USAGE)
		return (USAGE);
	return (0);
}

int			recup_command_nb(t_le *ledit, int i, int nb_del)
{
	int		j;
	int		x;

	if ((j = protect_atoi(ledit->buffer + i, 0)) < 0)
		return (unexpected_token("newline"));
	x = j;
	while (x > 9)
	{
		nb_del++;
		x = x / 10;
	}
	nb_del++;
	while (ledit->index_buffer > i + nb_del)
		left_arrow_move_cursor(ledit);
	while (nb_del + 1 > 0)
	{
		nb_del--;
		touch_del_character(ledit);
	}
	if ((copy_line_hist_front(&ledit->list_histo, ledit, j)) == USAGE)
		return (USAGE);
	return (0);
}

int			recup_command_compare(t_le *ledit, int i)
{
	int		j;

	j = i;
	while (ledit->buffer[j] && ledit->buffer[j] != ' ' \
			&& ledit->buffer[j] != ')')
		j++;
	j = j - i;
	if ((check_on_list_compare(&ledit->list_histo, ledit, i, j)) == USAGE)
		return (USAGE);
	return (0);
}

int			recup_history(t_le *ledit, int i)
{
	if (ledit->buffer[i + 1] && ledit->buffer[i + 1] == '!')
	{
		if ((recup_last_command(ledit, i + 2)) == USAGE)
			return (USAGE);
	}
	else if (ledit->buffer[i + 1] && ledit->buffer[i + 1] == '-')
	{
		if ((recup_command_nb_inverse(ledit, i + 2, 0)) == USAGE)
			return (USAGE);
	}
	else if (ledit->buffer[i + 1] && ft_isdigit(ledit->buffer[i + 1]) == 1)
	{
		if ((recup_command_nb(ledit, i + 1, 0)) == USAGE)
			return (USAGE);
	}
	else if (ledit->buffer[i + 1] && ft_isalpha(ledit->buffer[i + 1]) == 1)
	{
		if ((recup_command_compare(ledit, i + 1)) == USAGE)
			return (USAGE);
	}
	else
		return (unexpected_token("newline"));
	move_cursor_to_the_end(ledit);
	list_to_the_end(ledit);
	return (0);
}
