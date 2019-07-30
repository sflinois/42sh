/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 08:12:29 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/08 16:52:21 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir_exec.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void		save_fd(int *standart_fd, t_lst_fd **lst)
{
	*standart_fd = dup(STDERR_FILENO);
	fd_lst_add(STDIN_FILENO, lst);
	fd_lst_add(STDOUT_FILENO, lst);
	fd_lst_add(STDERR_FILENO, lst);
	fd_lst_add(*standart_fd, lst);
}

void		restore_fd(int *standart_fd, t_lst_fd **lst)
{
	int		tmp;

	while (*lst)
	{
		if ((*lst)->fd == *standart_fd && (*lst)->next == NULL)
		{
			tmp = dup(*standart_fd);
			fd_lst_close(*standart_fd, lst, &tmp);
			dup(tmp);
			dup(tmp);
		}
		else if ((*lst)->fd == *standart_fd)
		{
			fd_lst_close((*lst)->next->fd, &(*lst)->next, standart_fd);
		}
		else
			fd_lst_close((*lst)->fd, lst, standart_fd);
	}
}

int			correct_redir_r(t_redir *redir)
{
	char		*tmp;
	size_t		i;

	tmp = redir->in;
	i = 0;
	while (ft_isdigit((tmp + 1)[i]))
		i++;
	if (i == ft_strlen((tmp + 1)))
		redir->i_in = ft_atoi(tmp + 1);
	else if (i == ft_strlen((tmp + 1)) - 1 && (tmp + 1)[i] == '-')
	{
		redir->i_in = i == 0 ? redir->i_out : ft_atoi(tmp + 1);
		redir->i_out = (redir->i_in == redir->i_out && i != 0)
			? redir->i_out : -2;
	}
	else
	{
		redir->in = ft_strdup(tmp + 1);
		free(tmp);
	}
	return (0);
}

int			correct_redir_l(t_redir *redir)
{
	char		*tmp;
	size_t		i;

	tmp = redir->out;
	i = 0;
	while (ft_isdigit((tmp + 1)[i]))
		i++;
	if (i == ft_strlen((tmp + 1)))
		redir->i_out = ft_atoi(tmp + 1);
	else if (i == ft_strlen((tmp + 1)) - 1 && (tmp + 1)[i] == '-')
	{
		redir->i_out = i == 0 ? redir->i_in : ft_atoi(tmp + 1);
		redir->i_in = (redir->i_out == redir->i_in && i != 0)
			? redir->i_in : -2;
	}
	return (0);
}
