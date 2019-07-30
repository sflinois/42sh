/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 18:11:05 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/25 18:56:02 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	check_nb_argv_exit(t_mini *shell)
{
	if (shell->nb_arg > 2)
	{
		ft_putendl("exit\n minishell: exit: too many arguments");
		return (USAGE);
	}
	return (SUCCESS);
}

void		free_struct_ledit(t_le *ledit)
{
	if (ledit->list_histo)
		free_list_prev(ledit);
	if (ledit->list_heredoc != NULL)
		free_list_heredoc(&ledit->list_heredoc);
	if (ledit->str_opt_c != NULL)
		free(ledit->str_opt_c);
}

void		free_struct_shell(t_mini *shell)
{
	reinitialize_keyboard();
	free_tab_in_struct(shell, 4);
}

int			builtin_exit(t_mini *shell)
{
	int		i;

	i = 0;
	if ((check_nb_argv_exit(shell)) == USAGE)
		return (USAGE);
	if (shell->nb_arg == 1)
		return (EXIT_LR);
	else if (shell->nb_arg == 2 && \
			(check_if_int(shell->tab_argv_split[1])) == 0)
	{
		i = ft_atoi(shell->tab_argv_split[1]);
		shell->last_return_son = i;
		ft_putendl("exit");
		return (EXIT_ARG);
	}
	else if (shell->nb_arg == 2 && \
			(check_if_int(shell->tab_argv_split[1])) == -1)
	{
		ft_putstr("exit\nminishell: exit: ");
		ft_putstr(shell->tab_argv_split[1]);
		ft_putendl(": numeric argument required");
		return (EXIT_LR);
	}
	return (SUCCESS);
}
