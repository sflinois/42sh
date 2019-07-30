/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_tkn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 14:40:10 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 15:33:35 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "error.h"

static int	add_maillon_list_tkn(t_lst_tkn **lst, int token, char *command)
{
	t_lst_tkn	*new_mail;

	if (((new_mail) = (t_lst_tkn*)malloc(sizeof(t_lst_tkn))) == NULL)
		return (MALLOC_FAIL);
	new_mail->next = NULL;
	new_mail->nb_order = token;
	if (command != NULL)
		new_mail->order = ft_strdup(command);
	else
		new_mail->order = ft_strdup("\n");
	if (new_mail->order == NULL)
	{
		free(new_mail);
		return (MALLOC_FAIL);
	}
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	(*lst)->next = new_mail;
	return (SUCCESS);
}

static int	create_list_tkn(t_lst_tkn **lst, int token, char *command)
{
	if ((((*lst)) = (t_lst_tkn*)malloc(sizeof(t_lst_tkn))) == NULL)
		return (MALLOC_FAIL);
	ft_bzero(((*lst)), sizeof(t_lst_tkn));
	(*lst)->next = NULL;
	(*lst)->nb_order = token;
	if (((*lst)->order = ft_strdup(command)) == NULL)
	{
		free(*lst);
		return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

int			add_token_to_list(t_lst_tkn **lst, int token, char *command)
{
	t_lst_tkn	*tmp;

	tmp = (*lst);
	if (!tmp)
	{
		if ((create_list_tkn(lst, token, command)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	else
	{
		if ((add_maillon_list_tkn(&tmp, token, command)) == MALLOC_FAIL)
		{
			free_list_tkn(lst);
			return (MALLOC_FAIL);
		}
	}
	return (SUCCESS);
}

void		free_tkn(t_lst_tkn *tkn)
{
	free(tkn->order);
	if (tkn->nb_order == T_REDI_R || tkn->nb_order == T_REDI_RR || \
			tkn->nb_order == T_REDI_L || tkn->nb_order == T_REDI_LL \
			|| tkn->nb_order == T_REDI_LR || tkn->nb_order == T_ERROR)
	{
		if (tkn->redir.in)
			free(tkn->redir.in);
		if (tkn->redir.out)
			free(tkn->redir.out);
		if (tkn->nb_order == T_REDI_LL)
			if (tkn->redir.arg_heredoc != NULL)
				free(tkn->redir.arg_heredoc);
	}
	free(tkn);
}

void		free_list_tkn(t_lst_tkn **lst)
{
	t_lst_tkn	*next_mail;
	t_lst_tkn	*tmp;

	tmp = (*lst);
	next_mail = NULL;
	if (tmp == NULL)
		return ;
	while (tmp)
	{
		next_mail = tmp->next;
		free_tkn(tmp);
		tmp = next_mail;
	}
}
