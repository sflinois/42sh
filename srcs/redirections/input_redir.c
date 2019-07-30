/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 09:59:50 by sflinois          #+#    #+#             */
/*   Updated: 2019/04/02 15:59:39 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir_exec.h"

int		redir_input(char *file, int fd, t_lst_fd **fd_lst, int *standart_fd)
{
	int		open_fd;

	if (access(file, F_OK) != 0){
		ft_putstr_fd("21sh: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		return (print_redir_error(USAGE, ": No such file or directory"));
	}
	else
	{
		if (access(file, R_OK) != 0) {
			ft_putstr_fd("21sh: ", STDERR_FILENO);
			ft_putstr_fd(file, STDERR_FILENO);
			return (print_redir_error(USAGE, ": Permission denied"));
		}
		
	}
	open_fd = open(file, O_RDONLY, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	return (dup2_err(open_fd, fd, fd_lst, standart_fd));
}

int		redir_heredoc(char *str, t_lst_fd **fd_lst, int *standart_fd)
{
	int		open_fd;
	int		fdpipe[2];
	int		save;
	int		ret;

	ret = 0;
	if ((ret = pipe(fdpipe)) == -1)
		return (print_redir_error(ret, "ERROR: Pipe creation failed\n"));
	if ((save = dup(STDOUT_FILENO)) == -1)
		return (print_redir_error(save, "ERROR: dup failed\n"));
	if ((ret = dup2_err(fdpipe[1], STDOUT_FILENO, fd_lst, standart_fd)) < 0)
		return (ret);
	if (str)
		ft_putstr(str);
	if ((ret = dup2(save, STDOUT_FILENO)) == -1)
		return (print_redir_error(ret, "ERROR: dup2 failed\n"));
	close(fdpipe[1]);
	close(save);
	if ((open_fd = dup2_err(fdpipe[0], STDIN_FILENO, fd_lst, standart_fd)) < 0)
		return (open_fd);
	return (fd_lst_add(open_fd, fd_lst));
}
