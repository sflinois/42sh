/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 14:49:14 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/12 16:01:59 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

int				print_hash_error(int err_type, char *cmd)
{
	if (err_type == USAGE)
		ft_putstr_fd("hash: usage: hash [-r] [-p pathname] [name ...]\n"
						, STDERR_FILENO);
	if (err_type == EXIT_ARG)
	{
		ft_putstr_fd("hash: ", STDERR_FILENO);
		if (cmd)
			ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": not found\n", STDERR_FILENO);
	}
	return (err_type);
}

void			print_hashtable(t_ht *ht[HT_SIZE])
{
	int		i;
	int		is_empty;

	i = 0;
	is_empty = 1;
	while (i < HT_SIZE)
	{
		if (ht[i])
		{
			if (ht[i]->cmd != NULL)
			{
				if (is_empty)
				{
					ft_printf("%-8s%-150s\n", "hits", "command");
					is_empty = 0;
				}
				ft_printf("%4i%4c%-150s\n", ht[i]->hits, ' ', ht[i]->path);
			}
		}
		i++;
	}
}

int				is_path(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int				add_to_hashtable(t_mini *shell, t_ht *ht[HT_SIZE],
									char **cmd_tab, char *path)
{
	int		i;

	i = 0;
	while (cmd_tab[i])
	{
		if (path)
			ht_insert(ht, cmd_tab[i], path);
		else if (!is_path(cmd_tab[i]))
		{
			if (check_good_path(shell, cmd_tab, 0, 0))
			{
				ht_insert(ht, cmd_tab[i], shell->good_path);
				free(shell->good_path);
			}
			else
				return (print_hash_error(EXIT_ARG, cmd_tab[i]));
		}
		i++;
	}
	return (0);
}

t_err			builtin_hash(t_mini *shell)
{
	int		ret;
	int		is_reset;
	char	*path;
	int		cmd_index;

	is_reset = 0;
	path = NULL;
	cmd_index = 0;
	if ((ret = pars_hash_args(shell->tab_argv_split, &is_reset,
									&path, &cmd_index)))
		return (ret);
	if (is_reset)
	{
		ht_clear(shell->ht);
		return (SUCCESS);
	}
	if (path == NULL && cmd_index == 0)
		print_hashtable(shell->ht);
	else
		add_to_hashtable(shell, shell->ht,
						&(shell->tab_argv_split[cmd_index]), path);
	return (SUCCESS);
}
