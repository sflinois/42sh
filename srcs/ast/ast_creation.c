/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:15:58 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/15 11:42:50 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

/*
**	split the token list (lst) where tkn is found
*/

void		free_ast(t_ast *ast)
{
	if (ast->left)
	{
		free_ast(ast->left);
		ast->left = NULL;
	}
	if (ast->right)
	{
		free_ast(ast->right);
		ast->right = NULL;
	}
	if (ast->token)
	{
		free_list_tkn(&(ast->token));
		ast->token = NULL;
	}
	free(ast);
}

void		split_lst_tkn(t_lst_tkn *lst, t_lst_tkn *tkn)
{
	if (!lst || !tkn)
		return ;
	while (lst->next)
	{
		if (lst->next == tkn)
		{
			lst->next = NULL;
			return ;
		}
		lst = lst->next;
	}
}

t_lst_tkn	*search_tkn(t_lst_tkn *lst, int mode)
{
	t_lst_tkn	*lst_tkn;
	t_lst_tkn	*ret;

	lst_tkn = lst;
	ret = NULL;
	while (lst_tkn)
	{
		if (mode == 2
			&& (lst_tkn->nb_order == T_SEMICO || lst_tkn->nb_order == T_JOB))
		{
			split_lst_tkn(lst, lst_tkn);
			return (lst_tkn);
		}
		if (mode && (lst_tkn->nb_order == T_OR || lst_tkn->nb_order == T_AND))
			ret = lst_tkn;
		else if (!mode && lst_tkn->nb_order == T_PIPE)
		{
			split_lst_tkn(lst, lst_tkn);
			return (lst_tkn);
		}
		lst_tkn = lst_tkn->next;
	}
	if (ret)
		split_lst_tkn(lst, ret);
	return (ret);
}

t_ast		*create_ast(t_lst_tkn *lst)
{
	t_ast		*ret;
	t_lst_tkn	*tkn;

	ret = NULL;
	if (lst)
		ret = (t_ast*)ft_memalloc(sizeof(t_ast));
	if ((tkn = search_tkn(lst, 2))
		|| (tkn = search_tkn(lst, 1))
		|| (tkn = search_tkn(lst, 0)))
	{
		ret->left = create_ast(lst);
		ret->right = tkn->next == NULL ? NULL : create_ast(tkn->next);
		ret->token = tkn;
		ret->token->next = NULL;
	}
	else if (lst)
	{
		ret->left = NULL;
		ret->right = NULL;
		ret->token = lst;
	}
	return (ret);
}
