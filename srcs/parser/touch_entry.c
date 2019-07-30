/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_entry.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/26 15:55:17 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:42:53 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

int			reinitialize_var(t_le *ledit, int buffer)
{
	ledit->prompt = 0;
	ledit->index_buffer = 0;
	ledit->save_index_select = 0;
	ledit->copy_index = 0;
	ledit->sens_select = 0;
	ledit->limits_back_x = 0;
	ledit->nb_break_line = 0;
	ledit->c_del = 0;
	ledit->nb_inhib_miss = 0;
	ledit->index_histo = 0;
	ledit->start_cut = 0;
	if (ledit->save_line_loading == 1)
	{
		free(ledit->line_loading);
		ledit->save_line_loading = 0;
	}
	list_to_the_end(ledit);
	ft_putchar('\n');
	if (buffer == 1)
		ft_bzero(ledit->buffer, sizeof(char) * 2048);
	return (0);
}

static int	if_inhib_miss(t_le *ledit)
{
	char	*str;
	int		i;

	i = 0;
	str = "         >";
	if (ledit->index_buffer == (int)ft_strlen(ledit->buffer))
	{
		print_character(ledit, "\n");
		if (ledit->i_return == 0)
			ft_putstr("\x1B[32m");
		else
			ft_putstr("\x1B[31m");
		ft_putstr(str);
		ft_putstr("\033[0m");
		ledit->limits_back_x = ledit->index_buffer;
		ledit->c_del = 0;
	}
	return (0);
}

int			pars_final_string(t_le *ledit)
{
	int		ret;

	ret = 1;
	move_cursor_to_the_end(ledit);
	list_to_the_end(ledit);
	if (check_full_space(ledit->buffer, 0) == TRUE)
		return (reinitialize_var(ledit, 1));
	if ((parse_syntax_string(ledit)) == USAGE)
		return (USAGE);
	if ((ret = verif_heredoc(ledit, ledit->buffer, 0)) == FALSE)
		return (if_inhib_miss(ledit));
	else if (ret == MALLOC_FAIL)
		return (MALLOC_FAIL);
	else
		get_arg_heredoc(ledit->buffer, ledit, 0);
	if ((verif_miss_inhib(ledit->buffer, 0)) == FALSE)
		return (if_inhib_miss(ledit));
	if ((parse_full_backslashn(ledit->buffer)) == FALSE)
		return (reinitialize_var(ledit, 1));
	if ((check_if_semico(ledit->buffer)) == USAGE)
		return (USAGE);
	return (1);
}
