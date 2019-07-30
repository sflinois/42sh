/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 11:26:04 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/19 18:29:18 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	valid_line(t_mini *shell, t_le *ledit)
{
	int			ret;

	ret = 0;
	if ((transfere_list(&shell->list_final_eof, &ledit->list_heredoc)) != 0)
		return (check_error_return(MALLOC_FAIL, shell, ledit));
	if ((ret = (tokenize_tab_semico(shell, &shell->list_final_eof, ledit->buffer))) < 0)
		return (check_error_return(ret, shell, ledit));
	shell->nb_arg = 0;
	ledit->i_return = ret;
	ft_bzero(ledit->buffer, sizeof(char) * 2048);
	handle_jobs(&shell->jobs, FALSE);
	return (SUCCESS);
}

static int	loop_shell(t_mini *shell, t_le *ledit)
{
	int		ret;

	while (1)
	{
		if (ledit->prompt == 0)
			md_canon_print_prompt(ledit);
		if ((ret = go_read_and_stock(ledit, shell, 0)) < 0)
		{
			if ((ret = check_error_return(ret, shell, ledit)) != 0)
				return (ret);
		}
		else if (ret == 1)
		{
			if ((ret = valid_line(shell, ledit)) < 0)
			{
				if (ret >= EXIT_LR && ret <= EXIT_ARG)
					return (ret);
			}
		}
	}
	return (SUCCESS);
}

int			main(int argc, char **argv, char **env)
{
	t_mini		minishell;
	t_le		lineedit;
	int			ret;

	(void)argc;
	(void)argv;
	signal(SIGINT, SIG_IGN);
	ft_bzero(&minishell, sizeof(minishell));
	ft_bzero(&lineedit, sizeof(lineedit));
	if ((create_project_base(&minishell, &lineedit, env)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if ((md_canon_print_prompt(&lineedit)) == TERMCAPS)
	{
		free_tab_in_struct(&minishell, 4);
		return (TERMCAPS);
	}
	ft_bzero(lineedit.buffer, sizeof(char) * 2048);
	lineedit.size_prompt = ft_strlen("$My_21sh > ");
	if ((ret = loop_shell(&minishell, &lineedit)) < 0)
		return (ret);
}
