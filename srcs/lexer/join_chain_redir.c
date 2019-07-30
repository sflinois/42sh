/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_chain_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:34:30 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 15:31:13 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	join_arg_to_tkn(t_listenv *tmp, t_lst_tkn *list)
{
	if (tmp->str_env != NULL)
	{
		if ((list->redir.arg_heredoc = ft_strdup(tmp->str_env)) == NULL)
			return (MALLOC_FAIL);
	}
	else
		list->redir.arg_heredoc = NULL;
	return (0);
}

int			add_arg_heredoc(t_listenv **list_heredoc, t_lst_tkn **lst)
{
	t_listenv	*tmp;
	t_lst_tkn	*list;

	tmp = (*list_heredoc);
	list = (*lst);
	if (!tmp || !list)
		return (SUCCESS);
	while (list)
	{
		if (list->nb_order == T_REDI_LL)
		{
			if ((join_arg_to_tkn(tmp, list)) == MALLOC_FAIL)
			{
				free_list_shell(list_heredoc);
				return (MALLOC_FAIL);
			}
			tmp = tmp->next;
			if ((*list_heredoc)->str_env)
				free((*list_heredoc)->str_env);
			free((*list_heredoc));
			(*list_heredoc) = tmp;
		}
		list = list->next;
	}
	return (SUCCESS);
}
