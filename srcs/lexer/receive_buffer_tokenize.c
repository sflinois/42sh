/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_buffer_tokenize.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 15:50:06 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 15:30:45 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "ft_minishell.h"

static int	match_operator(char **buffer, t_lst_tkn **lst)
{
	int				i;
	int				tablex_size;
	static t_tablex	ltab[] = {
		{' ', &handle_space},
		{'\"', &handle_dquote},
		{'\'', &handle_squote},
		{'>', &handle_outredir},
		{'<', &handle_inredir},
		{'|', &handle_pipe},
		{'&', &handle_and},
		{';', &handle_semico},
	};

	tablex_size = 0;
	i = 0;
	tablex_size = (sizeof(ltab) / sizeof(t_tablex));
	while (i < tablex_size)
		if (**buffer == ltab[i++].oper)
			return (ltab[i - 1].fct(buffer, lst));
	return (handle_others(buffer, lst));
}

static int	tokenize_buffer(t_listenv **l_heredoc, char *str, t_lst_tkn **lst)
{
	(*lst) = NULL;
	while (*str && *str != '\0')
		match_operator(&str, lst);
	if ((add_arg_heredoc(l_heredoc, lst)) == MALLOC_FAIL)
	{
		free_list_tkn(lst);
		return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

int			tokenize_tab_semico(t_mini *shell, t_listenv **eof, char *buff)
{
	int			ret;
	t_lst_tkn	*lst;

	lst = NULL;
	if ((ret = tokenize_buffer(eof, buff, &lst)) < 0)
		return (ret);
	if ((ret = (exec_command(shell, &lst))) < 0)
		return (ret);
	return (ret);
}
