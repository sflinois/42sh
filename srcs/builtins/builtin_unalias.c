/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 15:13:44 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/31 18:37:52 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		clear_hashtable_alias(t_ht *h_alias[HT_SIZE])
{
	ht_clear(h_alias);
	return (SUCCESS);
}

void	ht_remove_one(t_ht **ht, char *key)
{
	int		i;
	t_ht	*tmp;

	i = ht_hash(key) % HT_SIZE;
	tmp = ht[i];
	if (tmp)
	{
		free(ht[i]->cmd);
		free(ht[i]->path);
		ht[i]->cmd = NULL;
		ht[i]->path = NULL;
		ht[i]->hits = 0;
		free(ht[i]);
		ht[i] = NULL;
	}
}

int		remove_alias_arg(t_ht *h_alias[HT_SIZE], char **args, int index)
{
	while (args[index])
	{
		ht_remove_one(h_alias, args[index]);
		index++;
	}
	return (SUCCESS);
}

int		builtin_unalias(t_mini *shell)
{
	int		index;
	int		opt;

	index = 1;
	opt = 0;
	if (shell->tab_argv_split[index] == NULL)
		return (error_options_alias("unaliass", ' ', 'a'));
	if (pars_unalias_options(shell->tab_argv_split, &index, &opt, 1) == USAGE)
		return (USAGE);
	if ((pars_unalias_args(shell->alias, \
			shell->tab_argv_split, index)) == USAGE)
		return (USAGE);
	if (opt)
		return (clear_hashtable_alias(shell->alias));
	else
		return (remove_alias_arg(shell->alias, shell->tab_argv_split, index));
	return (SUCCESS);
}
