/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 12:08:30 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/25 18:57:40 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static int	pars_all_arg(char **tabb)
{
	int		i;
	int		j;

	j = 0;
	i = 1;
	while (tabb[i])
	{
		if (ft_strclen(tabb[i], '=') > -1)
		{
			if (verif_all_param(tabb[i]) == -1)
				return (ft_print_error_set(tabb[i], 2));
		}
		else
		{
			while (tabb[i][j])
			{
				if (tabb[i][j] != '_' && if_alpha_or_digit(tabb[i][j]) == -1)
					return (ft_print_error_set(tabb[i], 2));
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (SUCCESS);
}

static char	*check_if_exist_on_set(t_listenv **lst, char *str)
{
	t_listenv	*tmp;
	int			i;
	int			d;

	d = 0;
	i = ft_strlen(str);
	tmp = (*lst);
	while (tmp)
	{
		d = ft_strclen(tmp->str_env, '=');
		if (d == i && ft_strncmp(str, tmp->str_env, i) == 0)
			return (ft_strdup(tmp->str_env));
		tmp = tmp->next;
	}
	return (NULL);
}

static void	add_all_arg(t_mini *shell, char **tabb)
{
	int		i;
	char	*str;

	i = 1;
	str = NULL;
	while (tabb[i])
	{
		if (ft_strclen(tabb[i], '=') > -1)
		{
			add_on_list_env(shell, &shell->list_set, tabb[i], 0);
			add_on_list_env(shell, &shell->list_env, tabb[i], 0);
		}
		else
		{
			if ((str = check_if_exist_on_set(&shell->list_set, tabb[i])) \
					!= NULL)
			{
				add_on_list_env(shell, &shell->list_env, str, 0);
				free(str);
			}
		}
		i++;
	}
}

int			builtin_export(t_mini *shell)
{
	int		ret;

	if ((ret = pars_all_arg(shell->tab_argv_split)) < 0)
		return (ret);
	add_all_arg(shell, shell->tab_argv_split);
	return (SUCCESS);
}
