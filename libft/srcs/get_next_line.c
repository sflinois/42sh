/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 19:33:45 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/05/21 15:36:54 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_push(t_list **tmp, t_list **list, char **line)
{
	char	*strverif;

	strverif = (char*)((*tmp)->content);
	if ((*tmp)->content && ft_strchr((*tmp)->content, '\n'))
	{
		(*line) = ft_strndup((*tmp)->content, \
				ft_strclen((*tmp)->content, '\n'));
		(*tmp)->content = ft_strdup((*tmp)->content + \
				(ft_strclen((*tmp)->content, '\n') + 1));
		free(strverif);
		(*tmp) = (*list);
		return (1);
	}
	else if (strverif[0] != '\0')
	{
		(*line) = ft_strdup((*tmp)->content);
		ft_bzero((*tmp)->content, ft_strlen((*tmp)->content));
		return (1);
	}
	return (0);
}

t_list		*verify_good_fd(int fd, t_list **list)
{
	t_list	*tmp;
	t_list	*start_list;

	start_list = (*list);
	if (*list)
	{
		while (*list)
		{
			if ((int)((*list)->content_size) == fd)
			{
				tmp = (*list);
				(*list) = start_list;
				return (tmp);
			}
			(*list) = (*list)->next;
		}
	}
	(*list) = start_list;
	tmp = ft_lstnew("", fd);
	ft_lstadd(list, tmp);
	return (*list);
}

int			get_next_line(const int fd, char **line)
{
	int				ret;
	char			buffer[BUFF_SIZE_GNL + 1];
	static t_list	*list = NULL;
	t_list			*start_list;
	t_list			*tmp;

	if (fd < 0 || !line || read(fd, NULL, 0))
		return (-1);
	start_list = list;
	tmp = verify_good_fd(fd, &list);
	while (!(ft_strchr(tmp->content, '\n')) && \
			(ret = read(fd, buffer, BUFF_SIZE_GNL)))
	{
		buffer[ret] = '\0';
		tmp->content = ft_strjoinfree(tmp->content, buffer, 1);
	}
	if ((ft_push(&tmp, &start_list, line)) == 1)
		return (1);
	return (0);
}
