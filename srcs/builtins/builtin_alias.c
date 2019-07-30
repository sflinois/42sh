/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 15:12:33 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/31 18:35:57 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "hashtable.h"
#include "libft.h"

static int	add_alias_to_hashtable(t_ht *h_alias[HT_SIZE], char *to_add)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	value = to_add + (ft_strclen(to_add, '=') + 1);
	key = str_keep_until_equal(to_add);
	ht_insert(h_alias, key, value);
	return (SUCCESS);
}

static int	print_alias_in_hashtable(t_ht *h_alias[HT_SIZE], char *to_print)
{
	ft_putstr_fd("alias ", 1);
	ft_putstr_fd(to_print, 1);
	ft_putchar_fd('=', 1);
	ft_putendl_fd(ht_search(h_alias, to_print), 1);
	return (SUCCESS);
}

static int	add_alias_args_or_print(t_ht *h_alias[HT_SIZE], char **args, int *i)
{
	while (args[*i])
	{
		if (ft_strclen(args[*i], '=') != -1)
			add_alias_to_hashtable(h_alias, args[*i]);
		else
			print_alias_in_hashtable(h_alias, args[*i]);
		(*i)++;
	}
	return (SUCCESS);
}

static int	print_all_alias(t_ht *h_alias[HT_SIZE])
{
	int		i;

	i = 0;
	while (i < HT_SIZE)
	{
		if (h_alias[i])
		{
			if (h_alias[i]->cmd != NULL)
			{
				ft_putstr_fd("alias ", 1);
				ft_putstr_fd(h_alias[i]->cmd, 1);
				ft_putchar_fd('=', 1);
				ft_putendl_fd(h_alias[i]->path, 1);
			}
		}
		i++;
	}
	return (SUCCESS);
}

int			builtin_alias(t_mini *shell)
{
	int		index;
	int		opt;

	index = 1;
	opt = 0;
	if (pars_alias_options(shell->tab_argv_split, &index, &opt, 1) == USAGE)
		return (USAGE);
	if ((pars_alias_args(shell->alias, shell->tab_argv_split, index)) == USAGE)
		return (USAGE);
	if (opt || shell->tab_argv_split[index] == NULL)
		print_all_alias(shell->alias);
	if (shell->tab_argv_split[index] == NULL)
		return (SUCCESS);
	else
		add_alias_args_or_print(shell->alias, shell->tab_argv_split, &index);
	return (SUCCESS);
}
