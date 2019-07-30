/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_position_cursor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 17:16:44 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 17:54:22 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	how_move_right_cursor(t_le *ledit, int nb_co)
{
	int		pos_col;
	int		i;

	i = 0;
	pos_col = 0;
	pos_col = ledit->size_prompt + ledit->index_buffer;
	while (pos_col > nb_co)
	{
		pos_col -= nb_co;
		i++;
	}
	while (i > 0)
	{
		ft_tc_up_cursor_one_line();
		i--;
	}
	while (pos_col > 0)
	{
		ft_tc_move_cursor_one_right();
		pos_col--;
	}
	ft_tc_save_position_cursor();
	ft_putchar('\n');
}

void	check_cursor_bottom_position(t_le *ledit, int pos_rows, \
		int nb_line_to_print, int i)
{
	int		nb_li;
	int		nb_backslashn;
	int		space_left;

	nb_backslashn = 0;
	nb_li = tgetnum("li");
	space_left = nb_li - pos_rows;
	nb_backslashn = space_left >= nb_line_to_print ? 0 : nb_line_to_print;
	if (nb_backslashn > 0)
	{
		while (nb_backslashn > 0)
		{
			write(1, "\n", 1);
			nb_backslashn--;
		}
		while (i < nb_line_to_print)
		{
			ft_tc_up_cursor_one_line();
			i++;
		}
		how_move_right_cursor(ledit, tgetnum("co"));
	}
	else
		ft_putchar('\n');
}

int		check_size_screen(int nb_line_to_print)
{
	int		nb_li;

	nb_li = tgetnum("li");
	if (nb_line_to_print >= nb_li - 3)
		return (-1);
	return (0);
}

int		completion_with_choise_or_not(t_le *ledit, int rows, t_comp *comp)
{
	int		nb_line_to_print;

	nb_line_to_print = comp->nb_mail / nb_arg_in_one_line(comp->max_len);
	if (comp->nb_mail % nb_arg_in_one_line(comp->max_len) != 0)
		nb_line_to_print++;
	if (check_size_screen(nb_line_to_print) == 0)
	{
		check_cursor_bottom_position(ledit, rows, nb_line_to_print, 0);
		print_lst_comp(comp);
	}
	else
	{
		print_lst_comp(comp);
		reinitialize_var(ledit, 0);
		print_my_prompt(ledit);
		ft_putstr(ledit->buffer);
		ledit->index_buffer = ft_strlen(ledit->buffer);
		return (-1);
	}
	return (SUCCESS);
}

void	get_position_cursor(int *rows, int i)
{
	char	buf[5];

	ft_bzero(&buf, sizeof(char) * 5);
	write(1, "\033[6n", 5);
	while (read(0, &(buf)[i], 1) < 5 && buf[i] != 'R')
		i++;
	i = 0;
	while (buf[i])
	{
		if (buf[i] >= '0' && buf[i] <= '9')
		{
			*rows = ft_atoi(&buf[i]);
			ft_bzero(&buf, sizeof(char) * 5);
			return ;
		}
		i++;
	}
}
