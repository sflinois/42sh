/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_or_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 10:56:04 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/14 16:45:41 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

t_err			check_same_var_env(t_listenv **copy, char *str, int j)
{
	t_listenv	*tmp;

	tmp = *copy;
	while (tmp)
	{
		if ((ft_strncmp(tmp->str_env, str, j)) == 0)
		{
			free(tmp->str_env);
			if ((tmp->str_env = ft_strdup(str)) == NULL)
				return (MALLOC_FAIL);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	if ((add_to_list(copy, str)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

int				verif_all_param(char *str)
{
	int		i;
	int		j;

	j = 1;
	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			j--;
		if (str[i] == '=' && i == 0)
			return (-1);
		if (str[i] != '_' && str[i] != '=' && \
				if_alpha_or_digit(str[i]) == -1 && j == 1)
		{
			return (-1);
		}
		i++;
	}
	if (j != 0)
		return (-1);
	return (0);
}

static t_err	go_to_add_set(t_mini *shell, char **tabb, int i)
{
	int		j;

	j = 0;
	(void)shell;
	while (tabb[i])
	{
		if (verif_all_param(tabb[i]) == -1)
			return (ft_print_error_set(tabb[i], 0));
		i++;
	}
	if (shell->list_set == NULL)
		if ((create_list_for_setenv(&shell->list_set, tabb[i++])) \
				== MALLOC_FAIL)
			return (MALLOC_FAIL);
	i = 0;
	while (tabb[i])
	{
		j = ft_strclen(tabb[i], '=');
		if ((check_same_var_env(&shell->list_set, tabb[i], j)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		i++;
	}
	return (SUCCESS);
}

static int		gateway_builtin_env(t_mini *shell, t_env *envs)
{
	int		ret;
	int		i;

	ret = 0;
	i = 0;
	if ((ret = start_command(shell, envs, &i)) < 0)
	{
		if (ret != MALLOC_FAIL)
			if (regenere_tab_env(shell, envs) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		return (ret);
	}
	if ((regenere_tab_env(shell, envs)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

int				check_variable_to_add(t_mini *shell, char **tabb)
{
	int		i;
	int		b;
	int		ret;
	t_env	envs;

	b = 0;
	i = 0;
	ret = 0;
	while (tabb[i])
	{
		if (ft_strclen(tabb[i], '=') == 0)
			return (print_error_write_equal_env(tabb, envs.options_env, i));
		else if (ft_strclen(tabb[i], '=') == -1)
		{
			if ((ret = gateway_builtin_env(shell, &envs)) < 0)
				return (ret);
			return (0);
		}
		i++;
	}
	if ((ret = go_to_add_set(shell, tabb, 0)) < 0)
		return (ret);
	return (0);
}
