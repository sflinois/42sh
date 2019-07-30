/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_tab_print_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 11:38:36 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/01 15:36:30 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

int		nb_arg_in_one_line(int max_len)
{
	int		nb_arg_line;
	int		nb_co;

	nb_co = tgetnum("co");
	nb_arg_line = nb_co / (max_len + 2);
	nb_arg_line = nb_arg_line < 1 ? 1 : nb_arg_line;
	return (nb_arg_line);
}

void	print_arg_limit_window(t_comp *comp, int *index_print, int *nb_arg)
{
	int		i;

	i = 0;
	(void)index_print;
	if (*nb_arg == 0)
	{
		*nb_arg = nb_arg_in_one_line(comp->max_len);
		write(1, "\n", 1);
	}
	if (comp->color != NULL)
		ft_putstr(comp->color);
	ft_putstr(comp->line);
	ft_putstr(RESET);
	while (i + comp->len_line < comp->max_len + 2)
	{
		write(1, " ", 1);
		i++;
	}
	(*nb_arg)--;
}

void	print_lst_comp(t_comp *comp)
{
	int		i;
	int		index_print;
	int		nb_arg;

	nb_arg = nb_arg_in_one_line(comp->max_len);
	index_print = 0;
	i = 1;
	while (comp->next)
	{
		print_arg_limit_window(comp, &index_print, &nb_arg);
		comp = comp->next;
		i++;
	}
	print_arg_limit_window(comp, &index_print, &nb_arg);
	i++;
	while (comp->prev)
	{
		comp->nb_mail = i;
		comp = comp->prev;
	}
	comp->nb_mail = i;
}

void	print_lst_mode_select(t_le *ledit, t_comp *comp, int index)
{
	int		nb_arg;

	nb_arg = nb_arg_in_one_line(comp->max_len);
	ft_tc_restaure_position_cursor();
	ft_putstr(ledit->buffer + ledit->index_buffer);
	ft_putchar('\n');
	while (comp)
	{
		if (index == 1)
		{
			ft_tc_select_mode();
			print_arg_limit_window(comp, &nb_arg, &nb_arg);
			ft_tc_end_select_mode();
		}
		else
			print_arg_limit_window(comp, &nb_arg, &nb_arg);
		index--;
		comp = comp->next;
	}
	ft_tc_restaure_position_cursor();
}
