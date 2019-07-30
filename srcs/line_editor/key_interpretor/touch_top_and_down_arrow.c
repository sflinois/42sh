/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_top_and_down_arrow.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 15:45:50 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:34:07 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static void	print_histo_reset_cursor(t_le *ledit, char *str)
{
	int		i;

	i = 0;
	ledit->limits_back_x = 0;
	move_cursor_to_the_start(ledit);
	ft_bzero(ledit->buffer, sizeof(char) * 2048);
	while (str && str[i])
	{
		print_character(ledit, str + i++);
		if (i > 0 && str[i - 1] == '\n')
		{
			if (ledit->i_return == 0)
				ft_putstr("\x1B[32m");
			else
				ft_putstr("\x1B[31m");
			ft_putstr("         >");
			ft_putstr("\033[0m");
			ledit->limits_back_x = i;
		}
	}
}

int			down_arrow_print_history(t_le *ledit)
{
	if (ledit->index_histo > 0 && ledit->list_histo)
	{
		if (ledit->index_histo > 0)
		{
			if (ledit->list_histo->next)
				ledit->list_histo = ledit->list_histo->next;
			else if (ledit->list_histo->next == NULL)
				ledit->index_histo = 0;
		}
		if (ledit->index_histo > 0 && ledit->list_histo->line[0])
			print_histo_reset_cursor(ledit, ledit->list_histo->line);
		else if (ledit->save_line_loading == 1)
		{
			print_histo_reset_cursor(ledit, ledit->line_loading);
			free(ledit->line_loading);
			ledit->line_loading = NULL;
			ledit->save_line_loading = 0;
		}
	}
	return (0);
}

int			top_arrow_print_history(t_le *ledit)
{
	int		i;

	i = 0;
	if (ledit->save_line_loading == 0)
		if ((copy_buffer_loading(ledit)) != SUCCESS)
			return (MALLOC_FAIL);
	if (ledit->list_histo)
	{
		if (ledit->index_histo == 1)
		{
			if (ledit->list_histo->prev)
				ledit->list_histo = ledit->list_histo->prev;
			else
				ledit->index_histo = 2;
		}
		if (ledit->index_histo < 2 && ledit->list_histo->line[i])
			print_histo_reset_cursor(ledit, ledit->list_histo->line);
		ledit->index_histo = 1;
	}
	return (0);
}

int			copy_buffer_loading(t_le *ledit)
{
	if (ledit->save_line_loading == 1)
		free(ledit->line_loading);
	if ((ledit->line_loading = ft_strdup(ledit->buffer)) == NULL)
		return (MALLOC_FAIL);
	ledit->save_line_loading = 1;
	return (SUCCESS);
}
