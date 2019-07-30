/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 14:40:50 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/15 11:51:27 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_EXEC_H
# define REDIR_EXEC_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "ast.h"
# include "ft_minishell.h"

typedef struct		s_lst_fd
{
	int				fd;
	struct s_lst_fd	*next;
}					t_lst_fd;

void				remove_redir_from_lst(t_lst_tkn **tkn_lst);
int					start_redir(t_lst_tkn **tkn_lst,
						t_lst_fd **fd_lst, int *standart_fd);

void				exec_cmd(const char *cmd,
						char *const argv[], char *const envp[]);
int					redir_input(char *file,
						int fd, t_lst_fd **fd_lst, int *standart_fd);
int					redir_heredoc(char *str,
						t_lst_fd **fd_lst, int *standart_fd);
int					redir_output(int fd,
						char *file, t_lst_fd **fd_lst, int *standart_fd);
int					redir_append(int fd,
						char *file, t_lst_fd **fd_lst, int *standart_fd);
int					redir_fd(int fd_close,
						int fd_dup, t_lst_fd **fd_lst, int *standart_fd);
int					close_fd(int fd_close,
						int fd_dup, t_lst_fd **fd_lst, int *standart_fd);
int					start_pipe(t_mini *shell, t_ast *ast);

void				save_fd(int *standard_fd, t_lst_fd **lst);
void				restore_fd(int *standard_fd, t_lst_fd **lst);
int					fd_lst_add(int fd, t_lst_fd **lst);
int					fd_lst_close(int fd, t_lst_fd **lst, int *standart_fd);
int					fd_lst_search(int fd, t_lst_fd **lst);
int					correct_redir_r(t_redir *redir);
int					correct_redir_l(t_redir *redir);

int					open_err(const char *pathname,
						int flags, t_lst_fd	**lst_fd);
int					close_err(int fd, t_lst_fd	**lst_fd);
int					dup_err(int oldfd, t_lst_fd	**lst_fd);
int					dup2_err(int oldfd, int newfd,
						t_lst_fd	**lst_fd, int *standart_fd);
int					pipe_err(int pipefd[2], t_lst_fd	**lst_fd);
int					print_redir_error(int err, char *str);
#endif
