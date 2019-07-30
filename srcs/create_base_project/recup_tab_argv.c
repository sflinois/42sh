/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_tab_argv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:27:46 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:23:34 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

char		**recup_tab_argv(char *str)
{
	int		i;
	char	**tabb;

	i = 0;
	delete_space_local(str);
	if ((tabb = ft_strsplit_miss(str, ';')) == NULL)
		return (NULL);
	while (tabb[i])
	{
		tabb[i] = ft_strtrim(tabb[i], 1);
		i++;
	}
	return (tabb);
}

static int	nb_mail_to_trans(t_lst_tkn **lst)
{
	t_lst_tkn	*tmp;
	int			i;

	tmp = (*lst);
	i = 0;
	while (tmp)
	{
		if ((tmp->nb_order < 3 || tmp->nb_order > 7) && tmp->nb_order != 12)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char		**recup_tab_argv_split_from_list(t_mini *shell, t_lst_tkn **lst)
{
	t_lst_tkn	*tmp;
	char		**tabb;
	int			i;

	if ((replace_alias(shell, *lst)) == MALLOC_FAIL)
	{
		//verif les feee a faire
		return (NULL);
	}
	tmp = (*lst);
	i = nb_mail_to_trans(lst);
	shell->nb_arg = i;
	if (i == 0)
		return (NULL);
	if ((tabb = (char**)malloc(sizeof(*tabb) * (i + 1))) == NULL)
		return (NULL);
	tabb[i] = NULL;
	i = 0;
	while (tmp)
	{
		if ((tmp->nb_order < 3 || tmp->nb_order > 7) && tmp->nb_order != 12)
			tabb[i++] = ft_strdup(tmp->order);
		tmp = tmp->next;
	}
	return (tabb);
}

void		recup_nb_arg(t_mini *shell, char **tabb)
{
	shell->nb_arg = 0;
	while (tabb[shell->nb_arg])
		shell->nb_arg++;
}
