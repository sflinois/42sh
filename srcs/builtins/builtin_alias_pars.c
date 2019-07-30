/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias_pars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:27:17 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/31 18:37:04 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			pars_unalias_options(char **args, int *i, int *opt, int j)
{
	while (args[*i])
	{
		if (args[*i][0] == '-')
		{
			if (args[*i][j] == '\0')
				return (error_options_alias("unalias", 'x', 'a'));
			while (args[*i][j])
			{
				if (args[*i][j] != 'a')
					return (error_options_alias("unalias", args[*i][j], 'a'));
				else
					*opt = 1;
				j++;
			}
			j = 1;
		}
		else
			return (SUCCESS);
		(*i)++;
	}
	return (SUCCESS);
}

int			pars_unalias_args(t_ht **h_alias, char **args, int i)
{
	while (args[i])
	{
		if (ft_strcmp(args[i], "alias") == 0 \
			|| ft_strcmp(args[i], "unalias") == 0)
			return (error_alias_use_alias_unalias("unalias", args[i]));
		if (ht_search(h_alias, args[i]) == NULL)
			return (error_not_found_alias("unalias", args[i]));
		i++;
	}
	return (SUCCESS);
}

int			pars_alias_options(char **args, int *i, int *opt, int j)
{
	while (args[*i])
	{
		if (args[*i][0] == '-')
		{
			if (args[*i][j] == '\0')
				return (error_options_alias("alias", 'x', 'p'));
			while (args[*i][j])
			{
				if (args[*i][j] != 'p')
					return (error_options_alias("alias", args[*i][j], 'p'));
				else
					*opt = 1;
				j++;
			}
			j = 1;
		}
		else
			return (SUCCESS);
		(*i)++;
	}
	return (SUCCESS);
}

int			pars_alias_args(t_ht **h_alias, char **args, int i)
{
	while (args[i])
	{
		if (ft_strcmp(args[i], "alias") == 0 \
			|| ft_strcmp(args[i], "unalias") == 0)
			return (error_alias_use_alias_unalias("alias", args[i]));
		if (ft_strclen(args[i], '=') == -1 \
			&& ht_search(h_alias, args[i]) == NULL)
			return (error_not_found_alias("alias", args[i]));
		i++;
	}
	return (SUCCESS);
}
