/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 10:00:06 by sflinois          #+#    #+#             */
/*   Updated: 2019/04/02 15:59:37 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir_exec.h"
#include "error.h"

int		redir_output(int fd, char *file, t_lst_fd **fd_lst, int *standart_fd)
{
	int				open_fd;
	struct stat 	stats;

	if (stat(file, &stats))
		return (print_redir_error(USAGE, "21sh: lstat failed"));
	if (S_ISLNK(stats.st_mode) || S_ISDIR(stats.st_mode)){
		ft_putstr_fd("21sh: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		return (print_redir_error(USAGE, ": Is a directory"));
	}
	if (access(file, F_OK) == 0 && access(file, W_OK) != 0) {
		ft_putstr_fd("21sh: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		return (print_redir_error(USAGE, ": Permission denied"));
	}
	open_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

	return (dup2_err(open_fd, fd, fd_lst, standart_fd));
}

int		redir_append(int fd, char *file, t_lst_fd **fd_lst, int *standart_fd)
{
	int		open_fd;
	struct stat 	stats;

	if (stat(file, &stats))
		return (print_redir_error(USAGE, "21sh: lstat failed"));
	if (S_ISLNK(stats.st_mode) || S_ISDIR(stats.st_mode)){
		ft_putstr_fd("21sh: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		return (print_redir_error(USAGE, ": Is a directory"));
	}
	if (access(file, F_OK) == 0 && access(file, W_OK) == 0) {
		ft_putstr_fd("21sh: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		return (print_redir_error(USAGE, ": Permission denied"));
	}
	open_fd = open(file, O_WRONLY | O_CREAT | O_APPEND,
		S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);
	return (dup2_err(open_fd, fd, fd_lst, standart_fd));
}

int		redir_fd(int fd_close, int fd_dup, t_lst_fd **fd_lst, int *standart_fd)
{
	if (fd_close == fd_dup)
		return (0);
	if (!fd_lst_search(fd_close, fd_lst))
		return (print_redir_error(USAGE, "21sh: Bad file descriptor"));
	if (fd_dup < 0)
	{
		fd_lst_close(fd_close, fd_lst, standart_fd);
		return (0);
	}
	return (dup2_err(fd_close, fd_dup, fd_lst, standart_fd));
}

int		close_fd(int fd_close, int fd_dup, t_lst_fd **fd_lst, int *standart_fd)
{
	int		open_fd;
	int		ret;

	if (fd_close == fd_dup)
		return (0);
	if ((ret = fd_lst_close(fd_close, fd_lst, standart_fd)) < 0)
		return (ret);
	if (fd_dup > 0)
	{
		ft_printf("DEBUG\nDEBUG part in close not supposed to go in !!\n");
		open_fd = dup(fd_dup);
		return (fd_lst_add(open_fd, fd_lst));
	}
	return (0);
}
