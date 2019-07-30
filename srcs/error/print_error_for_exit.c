/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_for_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:38:24 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/19 18:48:30 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

t_err	error_exit_return(int ret, t_mini *shell, t_le *ledit)
{
	free_struct_ledit(ledit);
	free_struct_shell(shell);
	if (ret == CTRL_D)
		ft_putendl_fd("\nexit", 1);
	else if (ret == MALLOC_FAIL)
		ft_putendl_fd("21sh: malloc error", 2);
	else if (ret == TERMCAPS)
		ft_putendl_fd("21sh: load termcaps error", 2);
	else if (ret == ERROR_CHARAC)
		ft_putendl_fd("21sh: character not supported", 2);
	else if (ret == EXIT_ARG || ret == EXIT_LR)
		return (ret);
	return (ret);
}

void	error_no_exit(t_le *ledit)
{
	ft_bzero(&ledit->buffer, sizeof(char) * 2048);
	if (ledit->list_heredoc != NULL)
		free_list_heredoc(&ledit->list_heredoc);
	if (ledit->str_opt_c != NULL)
		free(ledit->str_opt_c);
}

int		check_error_return(int ret, t_mini *shell, t_le *ledit)
{
	ledit->i_return = ret;
	handle_jobs(&shell->jobs, FALSE);
	if (ret >= EXIT_LR && ret <= EXIT_ARG)
	{
		if (ret == EXIT_ARG || ret == EXIT_LR || ret == CTRL_D)
			edit_file_histo(shell, ledit);
			// free jobs here
		return (error_exit_return(ret, shell, ledit));
	}
	else if (ret == USAGE || ret == OPEN_FAIL || ret == -2)
	{
		error_no_exit(ledit);
	}
	return (0);
}
