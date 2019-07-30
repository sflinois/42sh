/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_browsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 14:04:04 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/22 15:13:59 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_minishell.h"
#include "ast.h"
#include "redir_exec.h"

int			gateway_fork_background(t_mini *shell, t_ast *ast)
{
	pid_t	pid;
	t_job	*new_job;
	char	*job_name;

	shell->bg = TRUE;
	pid = fork();
	if (pid == 0)
	{
		shell->last_return_son = browse_ast(shell, ast);
		exit(shell->last_return_son);
	}
	else if (pid > 0)
	{
		job_name = get_job_name(ast);
		shell->last_return_son = SUCCESS;
		if ((new_job = add_job(&shell->jobs, job_name, pid)))
			waitpid(pid, &new_job->status, WNOHANG);
		else
			shell->last_return_son = MALLOC_FAIL;
		shell->bg = FALSE;
	}
	return (shell->last_return_son);
}

int			handle_ast_separator(t_mini *shell, t_ast *ast)
{
	int		ret;

	ret = 0;
	if (ast->token->nb_order == T_SEMICO)
	{
		browse_ast(shell, ast->left);
		if (ast->right != NULL)
			browse_ast(shell, ast->right);
	}
	else if (ast->token->nb_order == T_JOB)
	{
		if ((ret = gateway_fork_background(shell, ast->left)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		if (ast->right != NULL)
			ret = browse_ast(shell, ast->right);
	}
	return (ret);
}

int			handle_ast_operator(t_mini *shell, t_ast *ast)
{
	int		ret;

	ret = 0;
	if (ast->token->nb_order == T_AND || ast->token->nb_order == T_OR)
	{
		browse_ast(shell, ast->left);
		shell->pipe_on = 0;
		if ((!shell->last_return_son && ast->token->nb_order == T_AND)
			|| (shell->last_return_son && ast->token->nb_order == T_OR))
			browse_ast(shell, ast->right);
	}
	else if (ast->token->nb_order == T_PIPE)
	{
		shell->pipe_on = 1;
		start_pipe(shell, ast);
	}
	return (ret);
}

int			handle_ast_cmd(t_mini *shell, t_ast *ast)
{
	int			ret;
	int			standart_fd;
	int			err;
	t_lst_fd	*fd_lst;

	ret = 0;
	fd_lst = NULL;
	save_fd(&standart_fd, &fd_lst);
	err = start_redir(&ast->token, &fd_lst, &standart_fd);
	if (err)
	{
		shell->last_return_son = err;
		ret = err;
	}
	else
	{
		if ((ret = binary_or_builtin(shell, &ast)) == MALLOC_FAIL)
		{
			restore_fd(&standart_fd, &fd_lst);
			return (MALLOC_FAIL);
		}
	}
	restore_fd(&standart_fd, &fd_lst);
	return (ret);
}

int			browse_ast(t_mini *shell, t_ast *ast)
{
	int			ret;

	ret = 0;
	if (!ast)
		return (-1);
	if (ast->token->nb_order == T_SEMICO || ast->token->nb_order == T_JOB)
		ret = handle_ast_separator(shell, ast);
	else if (ast->token->nb_order == T_AND || ast->token->nb_order == T_OR
			|| ast->token->nb_order == T_PIPE)
		ret = handle_ast_operator(shell, ast);
	else
		ret = handle_ast_cmd(shell, ast);
	return (ret);
}

t_err		exec_command(t_mini *shell, t_lst_tkn **l)
{
	t_ast		*ast;
	int			ret;

	ast = create_ast(*l);
	ret = browse_ast(shell, ast);
	free_ast(ast);
	ast = NULL;
	shell->nb_arg = 0;
	return (ret);
}
