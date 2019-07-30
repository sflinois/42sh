/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:20:44 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:22:56 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	add_token_middle_list(t_lst_tkn **lst, char *to_add)
{
	t_lst_tkn	*tmp;
	t_lst_tkn	*new_mail;

	if ((new_mail = (t_lst_tkn*)malloc(sizeof(t_lst_tkn))) == NULL)
		return (MALLOC_FAIL);
	tmp = (*lst)->next;
	new_mail->next = tmp;
	new_mail->nb_order = T_COMMAND;
	if ((new_mail->order = ft_strdup(to_add)) == NULL)
	{
		free(new_mail);
		return (MALLOC_FAIL);
	}
	(*lst)->next = new_mail;
	return (SUCCESS);
}

static int	add_alias_lst(t_lst_tkn *lst, char *to_add)
{
	if (lst && lst->next == NULL)
	{
		if ((add_token_to_list(&lst, T_COMMAND, to_add)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	else if (lst && lst->next != NULL)
	{
		if ((add_token_middle_list(&lst, to_add)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

static int	split_new_alias_add_lst(t_lst_tkn *lst, char *new_alias)
{
	char	**tabb_split;
	int		i;

	i = 0;
	tabb_split = NULL;
	if ((tabb_split = ft_strsplit(new_alias, ' ')) == NULL)
		return (MALLOC_FAIL);
	free(lst->order);
	if ((lst->order = ft_strdup(tabb_split[i++])) == NULL)
	{
		ft_free_tab(tabb_split);
		return (MALLOC_FAIL);
	}
	while (tabb_split[i])
	{
		if ((add_alias_lst(lst, tabb_split[i++])) == MALLOC_FAIL)
		{
			ft_free_tab(tabb_split);
			return (MALLOC_FAIL);
		}
		lst = lst->next;
	}
	return (SUCCESS);
}

int			replace_alias(t_mini *shell, t_lst_tkn *lst)
{
	char	*new_alias;

	new_alias = NULL;
	while (lst)
	{
		if ((new_alias = ht_search(shell->alias, lst->order)) != NULL)
		{
			if (ft_strclen(new_alias, ' ') != -1)
			{
				if ((split_new_alias_add_lst(lst, new_alias)) == MALLOC_FAIL)
					return (MALLOC_FAIL);
			}
			else
			{
				free(lst->order);
				if ((lst->order = ft_strdup(new_alias)) == NULL)
					return (MALLOC_FAIL);
			}
		}
		lst = lst->next;
	}
	return (SUCCESS);
}
