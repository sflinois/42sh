/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 13:39:46 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/09 19:14:27 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static int	check_all_character(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '_' && if_alpha_or_digit(str[i]) == -1)
			return (-1);
		i++;
	}
	return (SUCCESS);
}

int			builtin_unset(t_mini *shell)
{
	int		i;

	i = 1;
	if (shell->list_set == NULL || shell->nb_arg == 1)
		return (error_unset());
	while (shell->tab_argv_split[i])
	{
		if (check_all_character(shell->tab_argv_split[i]) == -1)
			return (ft_print_error_set(shell->tab_argv_split[i], 1));
		i++;
	}
	i = 1;
	while (shell->tab_argv_split[i])
	{
		delete_on_list_env(shell, &shell->list_set, shell->tab_argv_split[i]);
		delete_on_list_env(shell, &shell->list_env, shell->tab_argv_split[i]);
		i++;
	}
	return (SUCCESS);
}
