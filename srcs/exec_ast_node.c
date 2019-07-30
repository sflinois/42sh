/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast_node.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/14 14:20:22 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 14:28:17 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_err		check_good_path(t_mini *shell, char **tabb, int i, int j)
{
	char *str;

	str = NULL;
	if (!(ft_strcmp(tabb[0], ".")) || !(ft_strcmp(tabb[0], "..")))
		return (error_command_not_found(tabb[j]));
	while (shell->no_path != 1 && shell->tab_env[i])
	{
		str = ft_strjoin(shell->tab_env[i], tabb[0]);
		if ((access(str, F_OK)) != 0)
			free(str);
		else
		{
			shell->good_path = str;
			return (1);
		}
		i++;
	}
	if (shell->no_path == 1 || shell->tab_env[i] == NULL)
		return (error_command_not_found(tabb[j]));
	return (SUCCESS);
}

int			exec_ast_node(t_mini *shell, t_listenv **list_env, char **tab_arg)
{
	int		ret;

	if ((ret = check_good_path(shell, tab_arg, 0, 0)) == 1)
	{
		if (!ht_search(shell->ht, tab_arg[0]))
			ht_insert(shell->ht, tab_arg[0], shell->good_path);
		else if (ft_strcmp(ht_search(shell->ht, tab_arg[0]), shell->good_path))
			ht_insert(shell->ht, tab_arg[0], shell->good_path);
		shell->ht[ht_hash(tab_arg[0]) % HT_SIZE]->hits++;
		return (go_for_fork(shell, tab_arg, list_env));
	}
	return (ret);
}

static int	exec_path(t_mini *shell, char **tabb)
{
	int		ret;

	ret = -1;
	if ((tabb[0][0] == '/') \
	|| (tabb[0][0] == '.' && tabb[0][1] == '/'))
	{
		ret = modifie_absolute_path(shell, \
			tabb[0], &shell->list_env, tabb);
	}
	else if (access(ht_search(shell->ht, tabb[0]), F_OK) == 0)
	{
		ret = modifie_absolute_path(shell, \
			ht_search(shell->ht, tabb[0]), \
			&shell->list_env, tabb);
	}
	return (ret);
}

int			binary_or_builtin(t_mini *shell, t_ast **ast)
{
	int		ret;

	ret = 0;
	if ((shell->tab_argv_split = \
	recup_tab_argv_split_from_list(shell, &(*ast)->token)) == NULL)
		return (MALLOC_FAIL);
	ret = check_builtin(shell, shell->tab_argv_split);
	if (ret == 1)
	{
		if ((ret = exec_path(shell, shell->tab_argv_split)) == -1)
		{
			ret = exec_ast_node(shell, &shell->list_env, shell->tab_argv_split);
		}
	}
	ft_free_tab(shell->tab_argv_split);
	return (ret);
}
