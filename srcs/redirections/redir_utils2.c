/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 10:13:03 by sflinois          #+#    #+#             */
/*   Updated: 2019/04/01 16:03:57 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir_exec.h"

int		open_err(const char *pathname, int flags, t_lst_fd **lst_fd)
{
	int		ret;

	lst_fd = NULL;
	if ((ret = open(pathname, flags)) == -1)
		ft_putendl_fd("ERROR: open failed", 2);
	return (ret);
}

int		dup_err(int oldfd, t_lst_fd **lst_fd)
{
	int		ret;

	lst_fd = NULL;
	if ((ret = dup(oldfd)) == -1)
		ft_putendl_fd("ERROR: dup failed", 2);
	return (ret);
}

int		dup2_err(int oldfd, int newfd, t_lst_fd **lst_fd, int *standart_fd)
{
	int				ret;
	int				new_stdfd;
	struct stat 	stats;

	fstat(newfd, &stats);

	if (newfd == *standart_fd)
	{
		new_stdfd = dup(*standart_fd);
		*standart_fd = new_stdfd;
		fd_lst_add(*standart_fd, lst_fd);
	}
	fd_lst_add(oldfd, lst_fd);
	if ((ret = dup2(oldfd, newfd)) == -1)
		return (print_redir_error(USAGE, "ERROR: dup2 failed"));
	return (0);
}

int		pipe_err(int pipefd[2], t_lst_fd **lst_fd)
{
	int		ret;

	lst_fd = NULL;
	if ((ret = pipe(pipefd)) == -1)
		ft_putendl_fd("ERROR: pipe failed", 2);
	return (ret);
}

int		print_redir_error(int err, char *str)
{
	ft_putendl_fd(str, STDERR_FILENO);
	return (err);
}
