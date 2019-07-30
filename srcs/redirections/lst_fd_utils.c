/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_fd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 17:46:06 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/12 16:33:25 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir_exec.h"

int			fd_lst_add(int fd, t_lst_fd **lst)
{
	t_lst_fd *tmp;

	tmp = *lst;
	if (fd < 0)
		return (fd);
	if (*lst == NULL)
	{
		if ((*lst = ft_memalloc(sizeof(t_lst_fd))) == NULL)
			return (-1);
		(*lst)->fd = fd;
		return (0);
	}
	while (tmp->next != NULL)
		tmp = tmp->next;
	if ((tmp->next = ft_memalloc(sizeof(t_lst_fd))) == NULL)
		return (-1);
	tmp->next->fd = fd;
	return (0);
}

int			fd_lst_savestd(int *standart_fd, t_lst_fd **lst)
{
	*standart_fd = dup(*standart_fd);
	if (*standart_fd < 0)
		return (*standart_fd);
	fd_lst_add(*standart_fd, lst);
	return (*standart_fd);
}

void		fd_lst_delone(t_lst_fd **lst, t_lst_fd *del)
{
	*lst = (*lst)->next;
	close(del->fd);
	free(del);
}

int			fd_lst_close(int fd, t_lst_fd **lst, int *standart_fd)
{
	t_lst_fd	*tmp;

	if (*lst == NULL)
		return (0);
	if ((*lst)->fd == fd)
	{
		if (fd == *standart_fd && fd_lst_savestd(standart_fd, lst) < 0)
			return (*standart_fd);
		fd_lst_delone(lst, *lst);
		return (1);
	}
	tmp = *lst;
	while (tmp->next != NULL && tmp->next->fd != fd)
		tmp = tmp->next;
	if (tmp->next)
	{
		if (fd == *standart_fd && fd_lst_savestd(standart_fd, lst) < 0)
			return (*standart_fd);
		fd_lst_delone(&(tmp->next), tmp->next);
		return (1);
	}
	return (0);
}

int			fd_lst_search(int fd, t_lst_fd **lst)
{
	t_lst_fd	*tmp;

	tmp = *lst;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
