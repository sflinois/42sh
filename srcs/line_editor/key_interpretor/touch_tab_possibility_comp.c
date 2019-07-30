/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_tab_possibility_comp.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 14:11:43 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 17:53:00 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

static void	complete_word(t_le *ledit, t_comp *comp, int index, int len_s)
{
	while (len_s > 0 && comp && comp->in_dir == 0)
	{
		touch_del_character(ledit);
		len_s--;
	}
	len_s = 0;
	while (comp)
	{
		if (index == 1)
		{
			while (comp->line[len_s])
				print_character(ledit, comp->line + len_s++);
		}
		index--;
		comp = comp->next;
	}
}

static void	touch_tab_comp(t_le *ledit, t_comp **comp, int *index)
{
	(*index)++;
	(*index) = (*index) >= (*comp)->nb_mail ? 1 : (*index);
	ft_tc_restaure_position_cursor();
	ft_tc_clear_after_cursor();
	print_lst_mode_select(ledit, *comp, *index);
}

static int	touch_entry_comp(t_le *ledit, t_comp **comp, int index, int len_s)
{
	ft_tc_restaure_position_cursor();
	ft_tc_clear_after_cursor();
	if (index > 0)
		complete_word(ledit, *comp, index, len_s);
	else
	{
		ft_putstr(ledit->buffer + ledit->index_buffer);
		ft_tc_restaure_position_cursor();
	}
	return (0);
}

static int	do_choise_completion(t_le *ledit, t_comp **comp, int i, int len_s)
{
	char	buf[6];
	int		rows;

	rows = 0;
	ft_bzero(&buf, sizeof(char) * 6);
	get_position_cursor(&rows, 0);
	if ((completion_with_choise_or_not(ledit, rows, (*comp))) == -1)
		return (0);
	ft_tc_restaure_position_cursor();
	while (42)
	{
		read(0, buf, 1);
		if (buf[0] == 9)
			touch_tab_comp(ledit, comp, &i);
		else if (buf[0] == 10)
			return (touch_entry_comp(ledit, comp, i, len_s));
		else if (buf[0] == 127)
		{
			touch_del_character(ledit);
			return (touch_entry_comp(ledit, comp, 0, 0));
		}
		else if ((buf[0] == 3 && buf[1] == 0) || (buf[0] == 27 && buf[1] == 0))
			return (touch_entry_comp(ledit, comp, 0, 0));
	}
	return (0);
}

int			print_possibility_comp(t_le *ledit, t_comp **comp, int len_s)
{
	int		copy_i_buffer;
	int		nb_arg_in_line;

	nb_arg_in_line = 0;
	copy_i_buffer = ledit->index_buffer;
	ft_tc_save_position_cursor();
	if (*comp == NULL)
		return (0);
	else if ((*comp)->next == NULL)
		complete_word(ledit, *comp, 1, len_s);
	else
		do_choise_completion(ledit, comp, 0, len_s);
	free_list_completion(comp);
	return (0);
}
