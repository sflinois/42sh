/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_histo_in_buff.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:18:08 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 15:54:53 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static int	check_str_histo(t_le *ledit, char *str)
{
	int		j;

	j = 0;
	while (str[j])
	{
		if (str[j] == '!')
		{
			if (str[j + 1] && ft_strclen("!-", str[j + 1]) > -1)
				return (error_exclamation());
			else if (str[j + 1] && if_alpha_or_digit(str[j + 1]) == 1)
				return (error_exclamation());
		}
		j++;
	}
	j = 0;
	while (str[j])
	{
		print_character(ledit, str + j);
		j++;
	}
	return (0);
}

int			recup_last_command(t_le *ledit, int i)
{
	while (ledit->index_buffer > i)
		left_arrow_move_cursor(ledit);
	touch_del_character(ledit);
	touch_del_character(ledit);
	if (ledit->list_histo)
	{
		if (ledit->list_histo->line)
			return (check_str_histo(ledit, ledit->list_histo->line));
	}
	return (0);
}

int			copy_line_hist_back(t_listhisto **lst, t_le *ledit, int j)
{
	t_listhisto	*tmp;

	tmp = (*lst);
	if (!tmp)
		return (error_not_found());
	while (tmp->prev && j > 1)
	{
		j--;
		tmp = tmp->prev;
	}
	if (j != 1)
		return (error_not_found());
	else
		return (check_str_histo(ledit, tmp->line));
	return (0);
}

int			copy_line_hist_front(t_listhisto **lst, t_le *ledit, int j)
{
	t_listhisto	*tmp;

	tmp = (*lst);
	if (!tmp)
		return (error_not_found());
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	while (tmp && tmp->next && j > 1)
	{
		tmp = tmp->next;
		j--;
	}
	if (j != 1)
		return (error_not_found());
	else
		return (check_str_histo(ledit, tmp->line));
	return (0);
}

int			check_on_list_compare(t_listhisto **lst, t_le *ledit, int i, int j)
{
	t_listhisto		*tmp;

	tmp = (*lst);
	if (!tmp)
		return (USAGE);
	while (tmp && tmp->prev)
	{
		if (ft_strncmp(tmp->line, ledit->buffer + i, j) == 0)
		{
			while (ledit->index_buffer > i + j)
				left_arrow_move_cursor(ledit);
			while (j + 1 > 0)
			{
				touch_del_character(ledit);
				j--;
			}
			return (check_str_histo(ledit, tmp->line));
		}
		tmp = tmp->prev;
	}
	return (USAGE);
}
