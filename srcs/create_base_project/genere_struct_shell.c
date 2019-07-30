/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genere_struct_shell.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 13:48:21 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:25:20 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_err			free_tab_in_struct(t_mini *shell, int i)
{
	if (i == 2)
	{
		ft_free_tab(shell->tab_env);
	}
	else if (i == 3)
	{
		free_list_shell(&shell->list_env);
		ft_free_tab(shell->tab_env);
	}
	else if (i == 4)
	{
		free_list_shell(&shell->list_set);
		free_list_shell(&shell->list_env);
		ft_free_tab(shell->tab_env);
	}
	return (MALLOC_FAIL);
}

static t_err	initialize_var_internal(t_mini *shell, t_listenv **lst)
{
	char	*str;

	str = NULL;
	if ((recup_home(shell, &str)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (str == NULL)
		return (SUCCESS);
	if ((str = ft_strjoinfree("HISTFILE=", str, 2)) == NULL)
		return (MALLOC_FAIL);
	if ((str = ft_strjoinfree(str, "/.21sh_history", 1)) == NULL)
		return (MALLOC_FAIL);
	if ((add_to_list(lst, str)) != 0)
	{
		free(str);
		return (MALLOC_FAIL);
	}
	if ((add_to_list(lst, "HISTFILESIZE=250")) == MALLOC_FAIL)
	{
		free(str);
		return (MALLOC_FAIL);
	}
	free(str);
	return (SUCCESS);
}

t_err			create_project_base(t_mini *shell, t_le *ledit, char **env)
{
	int		ret;

	if ((recup_env(shell, env)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if ((create_list(&shell->list_env, env, 0)) != 0)
		return (free_tab_in_struct(shell, 2));
	if ((verif_required_env(shell, &shell->list_env)) != 0)
		return (free_tab_in_struct(shell, 3));
	if ((create_copy_list(&shell->list_set, &shell->list_env)) != 0)
		return (free_tab_in_struct(shell, 4));
	if ((initialize_var_internal(shell, &shell->list_set)) != 0)
		return (free_tab_in_struct(shell, 4));
	if ((ret = initialize_list_histo(shell, ledit, &ledit->list_histo)) < -1)
	{
		if (ret == ERROR_CHARAC)
		{
			ft_putstr("\x1B[31m$My_21sh > \033[0m");
			ft_putendl("21sh: read: not supported charac");
		}
		return (free_tab_in_struct(shell, 4));
	}
	ht_insert(shell->alias, "ls", "ls -G"); // SYLVAIN PROTECT MALLOC PLZ;
	return (SUCCESS);
}
