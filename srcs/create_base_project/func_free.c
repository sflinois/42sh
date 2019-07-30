/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 14:43:32 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/21 17:42:22 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "ft_lineedit.h"

void	free_list_heredoc(t_list_eof **to_free)
{
	t_list_eof	*next_mail;
	t_list_eof	*list;

	list = (*to_free);
	next_mail = NULL;
	if (!list)
		return ;
	while (list)
	{
		next_mail = list->next;
		if (list->str_arg != NULL)
			free(list->str_arg);
		free(list);
		list = next_mail;
	}
	(*to_free) = NULL;
}

void	free_list_shell(t_listenv **to_free)
{
	t_listenv	*next_mail;
	t_listenv	*list;

	list = (*to_free);
	next_mail = NULL;
	if (!list)
		return ;
	while (list)
	{
		next_mail = list->next;
		if (list->str_env != NULL)
			free(list->str_env);
		free(list);
		list = next_mail;
	}
	(*to_free) = NULL;
}

void	free_list_prev2(t_listhisto **to_free)
{
	t_listhisto	*next_mail;
	t_listhisto	*list;

	list = (*to_free);
	next_mail = NULL;
	if (!list)
		return ;
	while (list)
	{
		next_mail = list->next;
		if (list->line != NULL)
			free(list->line);
		free(list);
		list = next_mail;
	}
	(*to_free) = NULL;
}

void	free_list_prev(t_le *ledit)
{
	t_listhisto	*tmp;

	tmp = ledit->list_histo;
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	free_list_prev2(&tmp);
}
