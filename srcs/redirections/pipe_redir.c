/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 09:42:21 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/08 14:04:35 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	1 -> fork for pipe
**	2 -> create pipe
**	3 -> launch left
**  3.1 -> close read, dup stdout
**	3.2 -> browse tkn
**	4 -> launch right
**  4.1 -> close write, dup stdin
**	4.2 -> browse tkn
**	5 -> close pipe and wait pid
**	6 -> exit
*/

#include "ft_minishell.h"
#include "ast.h"

void	launch_left_pipe(t_mini *shell, t_ast *ast, int *fdpipe)
{
	close(fdpipe[0]);
	if (dup2(fdpipe[1], STDOUT_FILENO) == -1)
		ft_printf("ERROR: dup2 in left pipe");
	browse_ast(shell, ast->left);
	exit(0);
}

void	launch_right_pipe(t_mini *shell, t_ast *ast, int *fdpipe)
{
	close(fdpipe[1]);
	if (dup2(fdpipe[0], STDIN_FILENO) == -1)
		ft_printf("ERROR: dup2 in right pipe");
	browse_ast(shell, ast->right);
	exit(0);
}

void	launch_pipe(t_mini *shell, t_ast *ast)
{
	pid_t	left_pid;
	pid_t	right_pid;
	int		fdpipe[2];
	int		ret1;
	int		ret2;

	if (pipe(fdpipe) == -1)
		ft_printf("ERROR: Pipe creation failed\n");
	if ((left_pid = fork()) == -1)
		ft_printf("ERROR: Left pipe fork failed\n");
	else if (left_pid == 0)
		launch_left_pipe(shell, ast, fdpipe);
	if ((right_pid = fork()) == -1)
		ft_printf("ERROR: Right pipe fork failed\n");
	else if (right_pid == 0)
		launch_right_pipe(shell, ast, fdpipe);
	close(fdpipe[0]);
	close(fdpipe[1]);
	wait(&ret1);
	wait(&ret2);
	exit(0);
}

int		start_pipe(t_mini *shell, t_ast *ast)
{
	pid_t	pipe_pid;
	int		ret;

	ret = 0;
	if ((pipe_pid = fork()) == -1)
		ft_printf("ERROR: Pipe fork failed\n");
	else if (pipe_pid == 0)
		launch_pipe(shell, ast);
	wait(&ret);
	return (0);
}
