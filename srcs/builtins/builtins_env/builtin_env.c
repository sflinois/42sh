/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 16:13:41 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/25 19:06:01 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static t_err	send_to_exec(t_mini *shell, int *i, t_env *envs)
{
	char	**tabb;
	int		ret;

	tabb = NULL;
	ret = 0;
	tabb = realloc_tabb(shell, i, 0, 0);
	if ((ret = exec_ast_node(shell, &envs->copy_list_env, tabb)) < 0)
	{
		ft_free_tab(tabb);
		return (ret);
	}
	ft_free_tab(tabb);
	return (SUCCESS);
}

static t_err	do_copy_and_modify_list(t_mini *shell, t_env *envs, int *i)
{
	int		ret;

	ret = 0;
	if ((do_a_copy_env(shell, envs, &shell->list_env)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (envs->options_env > 0 && (ret = apply_options_env(shell, envs, i)) < 0)
		return (ret);
	else if ((ret = check_channge_variable_env(shell, envs, i, 0)) < 0)
		return (ret);
	return (SUCCESS);
}

t_err			start_command(t_mini *shell, t_env *envs, int *i)
{
	int		ret;

	if (*i < shell->nb_arg)
	{
		if ((ret = do_copy_and_modify_list(shell, envs, i)) < 0)
			return (ret);
		if (*i < shell->nb_arg)
		{
			if ((ret = send_to_exec(shell, i, envs)) < 0)
				return (ret);
		}
		else if ((envs->options_env & 1) == 0)
			ft_print_list(&envs->copy_list_env);
	}
	return (SUCCESS);
}

static	t_err	gateway_start_command(t_mini *shell, t_env *envs, int *i)
{
	int		ret;

	ret = 0;
	if ((ret = start_command(shell, envs, i)) < 0)
	{
		ret = regenere_tab_env(shell, envs);
		return (ret);
	}
	if ((ret = regenere_tab_env(shell, envs)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

t_err			builtin_env(t_mini *shell)
{
	int			i;
	int			ret;
	t_env		envs;

	i = 1;
	ft_bzero(&envs, sizeof(envs));
	envs.nb_arg = shell->nb_arg;
	if (shell->nb_arg > i)
	{
		if ((ret = recup_all_options_env(shell->tab_argv_split, &envs, &i)) < 0)
			return (ret);
	}
	if (shell->nb_arg > i)
	{
		if ((ret = gateway_start_command(shell, &envs, &i)) < 0)
			return (ret);
	}
	else
		print_list_for_env(shell, &envs);
	envs.options_env = 0;
	return (SUCCESS);
}
