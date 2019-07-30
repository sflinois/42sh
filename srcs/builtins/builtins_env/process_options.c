/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_options.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 18:01:41 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/14 16:50:00 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static int	pars_arg_options_i(t_mini *shell, t_env *envs, int *i, int a)
{
	int		ret;

	while (shell->tab_argv_split[*i])
	{
		if ((a = ft_strclen(shell->tab_argv_split[*i], '=')) != -1)
		{
			if (a == 0 || envs->options_env & 2)
				return (print_error_write_equal_env(shell->tab_argv_split, \
							envs->options_env, *i));
			else if (a > 0)
			{
				if ((ret = add_on_list_env(shell, \
				&envs->copy_list_env, shell->tab_argv_split[*i], 1)) < 0)
					return (ret);
			}
		}
		else if (ft_strcmp(shell->tab_argv_split[*i], "env") == 0)
		{
		}
		else
			return (0);
		(*i)++;
	}
	return (0);
}

static int	pars_arg_options_u(t_mini *shell, t_env *envs, int *i, int ret)
{
	while (shell->tab_argv_split[*i])
	{
		if (*i == 2)
		{
			if ((ret = ft_strclen(shell->tab_argv_split[*i], '=')) == -1)
				unsetenv_via_env(shell, envs, i);
			else
				return (print_error_write_equal_env(shell->tab_argv_split, \
							envs->options_env, *i));
		}
		else
		{
			if ((ret = ft_strclen(shell->tab_argv_split[*i], '=')) == -1)
				return (0);
			else
			{
				if ((ret = add_on_list_env(shell, &envs->copy_list_env, \
								shell->tab_argv_split[*i], 1)) < 0)
					return (ret);
			}
		}
		(*i)++;
	}
	return (0);
}

static int	pars_arg_options_iu(t_mini *shell, t_env *envs, int *i, int ret)
{
	if (shell->tab_argv_split[*i])
	{
		if ((ret = ft_strclen(shell->tab_argv_split[*i], '=')) == -1)
			unsetenv_via_env(shell, envs, i);
		else
		{
			return (print_error_write_equal_env(shell->tab_argv_split, \
						envs->options_env, *i));
		}
		(*i)++;
	}
	while (shell->tab_argv_split[*i])
	{
		if ((ret = ft_strclen(shell->tab_argv_split[*i], '=')) == -1)
			return (0);
		else
		{
			if ((ret = add_on_list_env(shell, &envs->copy_list_env, \
					shell->tab_argv_split[*i], 1)) < 0)
				return (ret);
		}
		(*i)++;
	}
	return (0);
}

int			apply_options_env(t_mini *shell, t_env *envs, int *i)
{
	int		ret;

	if (envs->options_env & 1 && (envs->options_env & 2) == 0)
	{
		if ((ret = pars_arg_options_i(shell, envs, i, 0)) < 0)
			return (ret);
	}
	else if ((envs->options_env & 1) == 0 && envs->options_env & 2)
	{
		if ((ret = pars_arg_options_u(shell, envs, i, 0)) < 0)
			return (ret);
	}
	else if (envs->options_env & 1 && envs->options_env & 2)
	{
		if ((ret = pars_arg_options_iu(shell, envs, i, 0)) < 0)
			return (ret);
	}
	envs->options_env = 0;
	return (0);
}
