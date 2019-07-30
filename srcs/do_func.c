/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_func.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 12:44:16 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 15:36:11 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"
#include "error.h"
#include "ft_lineedit.h"

void	exec_process_child(t_mini *shell, char **tabb, char **tab_env)
{
	if (!shell->bg)
	{
		reinitialize_keyboard();
		signal(SIGINT, SIG_DFL);
	}
	execve(shell->good_path, tabb, tab_env);
}

void	exec_process_parent(t_mini *shell, pid_t pid)
{
	int		exit_status;

	exit_status = 0;
	if (!shell->bg)
		waitpid(pid, &exit_status, 0);
	shell->last_return_son = exit_status;
}

void	do_fork(t_mini *shell, char **tabb, char **tab_env)
{
	pid_t	pid;

	pid = 0;
	if (!shell->bg)
		pid = fork();
	if (pid == 0)
		exec_process_child(shell, tabb, tab_env);
	else if (pid > 0)
		exec_process_parent(shell, pid);
}

int		go_for_fork(t_mini *shell, char **tabb, t_listenv **list)
{
	char	**tab_env;
	int		ret;

	ret = 0;
	tab_env = NULL;
	if ((tab_env = transfere_list_to_tab(tab_env, list, 0)) == NULL)
	{
		free(shell->good_path);
		return (MALLOC_FAIL);
	}
	do_fork(shell, tabb, tab_env);
	ft_free_tab(tab_env);
	free(shell->good_path);
	return (shell->last_return_son);
}
