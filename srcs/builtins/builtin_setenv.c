/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 18:27:19 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/25 19:00:39 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

t_err			create_list_for_setenv(t_listenv **tmp, char *str)
{
	t_listenv	*list;

	if ((list = (t_listenv*)malloc(sizeof(t_listenv))) == NULL)
		return (MALLOC_FAIL);
	ft_bzero(list, sizeof(t_listenv));
	(*tmp) = list;
	list->next = NULL;
	if (str != NULL)
	{
		if ((list->str_env = ft_strdup(str)) == NULL)
		{
			free(list);
			(*tmp) = NULL;
			return (MALLOC_FAIL);
		}
	}
	else if (str == NULL)
		list->str_env = NULL;
	return (SUCCESS);
}

static t_err	change_the_path(t_mini *shell, char *str, int i)
{
	char	*tmp;

	tmp = NULL;
	if (ft_strncmp(str, "PATH=", 4) == 0)
	{
		ft_free_tab(shell->tab_env);
		shell->no_path = 1;
		shell->tab_env = NULL;
		if (str[i + 1])
		{
			if ((tmp = ft_strdup(str + i + 1)) == NULL)
				return (MALLOC_FAIL);
			if ((change_env_and_join_local(shell, tmp)) == MALLOC_FAIL)
				return (MALLOC_FAIL);
			shell->no_path = 0;
		}
		else
			shell->no_path = 1;
	}
	return (SUCCESS);
}

static t_err	add_env_at_the_end(t_mini *shell, t_listenv **lst, \
		char *str, int i)
{
	if ((change_the_path(shell, str, i)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if ((*lst) == NULL)
	{
		if ((create_list_for_setenv(lst, str)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	else
	{
		if ((add_to_list(lst, str)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

t_err			add_on_list_env(t_mini *shell, t_listenv **lst, \
		char *str, int check)
{
	t_listenv	*l;
	int			i;
	int			d;

	i = ft_strclen(str, '=');
	l = (*lst);
	if (check == 1 && verif_all_param(str) == -1)
		return (ft_print_error_set(str, 0));
	while (l)
	{
		d = ft_strclen(l->str_env, '=');
		if (d == i && !(ft_strncmp(str, l->str_env, i)))
		{
			if ((change_the_path(shell, str, i)) == MALLOC_FAIL)
				return (MALLOC_FAIL);
			free(l->str_env);
			if ((l->str_env = ft_strdup(str)) == NULL)
				return (MALLOC_FAIL);
			return (SUCCESS);
		}
		l = l->next;
	}
	if ((add_env_at_the_end(shell, lst, str, i)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

t_err			builtin_setenv(t_mini *shell)
{
	int		ret;

	ret = 0;
	if ((ret = check_nb_arg(shell->nb_arg)) < 0)
		return (ret);
	if ((add_on_list_env(shell, &shell->list_env, \
					shell->tab_argv_split[1], 1)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}
