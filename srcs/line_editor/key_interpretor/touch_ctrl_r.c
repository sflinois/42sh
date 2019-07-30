/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_ctrl_r.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 18:33:59 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 11:35:18 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"

int		reinitialize_all_ledit(t_le *ledit)
{
	ft_bzero(&ledit->buffer, sizeof(char) * 2048);
	if (ledit->list_heredoc != NULL)
		free_list_heredoc(&ledit->list_heredoc);
	if (ledit->str_opt_c != NULL)
		free(ledit->str_opt_c);
	reinitialize_var(ledit, 0);
	return (-1);
}

int		valid_line_histo(t_le *ledit, int ret_histo)
{
	reinitialize_all_ledit(ledit);
	list_to_the_end(ledit);
	print_my_prompt(ledit);
	return (ret_histo);
}

int		search_in_histo(t_listhisto **lst, char *buffer, int j, int size)
{
	t_listhisto	*tmp;
	int			index_histo;

	index_histo = 0;
	tmp = (*lst);
	while (tmp)
	{
		if ((j = ft_strclen(tmp->line, buffer[0])) > -1)
		{
			if (ft_strncmp(tmp->line + j, buffer, size) == 0)
			{
				ft_tc_save_position_cursor();
				ft_putstr(" : ");
				ft_putstr(tmp->line);
				ft_tc_restaure_position_cursor();
				return (index_histo);
			}
		}
		else
			ft_tc_clear_after_cursor();
		index_histo++;
		tmp = tmp->prev;
	}
	return (-1);
}

int		print_histo_search(t_listhisto **lst, char *buffer)
{
	int			size;
	int			ret;

	ret = 0;
	if ((size = (int)ft_strlen(buffer)) == 0)
	{
		ft_tc_clear_after_cursor();
		return (-1);
	}
	if ((ret = search_in_histo(lst, buffer, 0, size)) != -1)
		return (ret);
	return (0);
}

int		ctrl_r_histo(t_le *ledit)
{
	char	buffer[520];
	char	buf_char[6];
	int		index;
	int		ret_histo;

	index = 0;
	ft_bzero(&buf_char, sizeof(char) * 6);
	ft_bzero(&buffer, sizeof(char) * 520);
	reinitialize_all_ledit(ledit);
	ft_putstr("(reverse-i-search) : ");
	while (42)
	{
		ret_histo = print_histo_search(&ledit->list_histo, buffer);
		read(0, buf_char, 6);
		if (buf_char[0] >= 32 && buf_char[0] <= 126 && buf_char[1] == 0)
			inser_char_buf_search(buffer, &index, buf_char);
		else if (buf_char[0] == 10)
			return (valid_line_histo(ledit, ret_histo));
		else if (buf_char[0] == 127)
			touch_del_buf_search(buffer, &index, 0, tgetnum("co"));
		else
			return (reinitialize_all_ledit(ledit));
	}
	return (0);
}
