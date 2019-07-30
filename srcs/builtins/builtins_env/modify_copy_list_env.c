/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_copy_list_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:33:18 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/25 19:07:12 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static t_err	pars_variable_add_built_env(char **tabb, int i)
{
	while (tabb[i] && ft_strclen(tabb[i], '=') > -1)
	{
		if (verif_all_param(tabb[i]) == -1)
			return (ft_print_error_set(tabb[i], 0));
		i++;
	}
	return (SUCCESS);
}

t_err			check_channge_variable_env(t_mini *shell, t_env *envs, \
		int *i, int j)
{
	char	*s;
	int		ret;

	s = NULL;
	if ((ret = pars_variable_add_built_env(shell->tab_argv_split, *i)) < 0)
		return (ret);
	while (shell->tab_argv_split[*i])
	{
		if ((j = ft_strclen(shell->tab_argv_split[*i], '=')) > -1)
		{
			if ((s = ft_strdup(shell->tab_argv_split[*i])) == NULL)
				return (MALLOC_FAIL);
			add_on_list_env(shell, &envs->copy_list_env, s, 0);
			free(s);
			(*i)++;
			if ((*i) < shell->nb_arg && ft_strcmp(shell->tab_argv_split[(*i)], \
						"env") == 0)
				(*i)++;
		}
		else
			return (SUCCESS);
	}
	return (SUCCESS);
}

t_err			create_copy_list(t_listenv **tmp, t_listenv **to_copy)
{
	t_listenv	*tmp_cp;

	tmp_cp = (*to_copy);
	if (((*tmp) = (t_listenv*)malloc(sizeof(t_listenv))) == NULL)
		return (MALLOC_FAIL);
	ft_bzero((*tmp), sizeof(t_listenv));
	(*tmp)->next = NULL;
	if (tmp_cp->str_env)
	{
		if (((*tmp)->str_env = ft_strdup(tmp_cp->str_env)) == NULL)
		{
			free((*tmp));
			(*tmp) = NULL;
			return (MALLOC_FAIL);
		}
		tmp_cp = tmp_cp->next;
	}
	while (tmp_cp)
	{
		if ((add_to_list(tmp, tmp_cp->str_env)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		tmp_cp = tmp_cp->next;
	}
	return (SUCCESS);
}

t_err			do_a_copy_env(t_mini *shell, t_env *envs, t_listenv **env)
{
	if (envs->options_env & 1)
	{
		envs->copy_list_env = NULL;
		if ((change_env_and_join_local(shell, NULL)) != 0)
			return (MALLOC_FAIL);
	}
	if ((envs->options_env & 1) == 0)
	{
		if (env && (*env))
		{
			if ((create_copy_list(&envs->copy_list_env, env)) != 0)
				return (MALLOC_FAIL);
		}
		else
			envs->copy_list_env = NULL;
	}
	return (SUCCESS);
}
