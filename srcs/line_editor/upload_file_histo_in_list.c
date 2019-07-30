/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upload_file_histo_in_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 12:01:14 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/29 15:48:33 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int				open_file_histo(char *str, int flags)
{
	int		fd_file;

	if ((fd_file = open(str, flags)) == -1)
	{
		ft_putstr("\x1B[31m$My_21sh > \033[0m");
		ft_putendl("21sh: open: .21sh_history fail");
		free(str);
		return (-1);
	}
	return (fd_file);
}

static t_err	fill_list_histo(t_le *ledit, int fd, int size_file, char *del)
{
	char	*str;

	str = NULL;
	while (get_next_line(fd, &str))
	{
		if (size_file < 249)
		{
			if ((stock_line_for_histo(ledit, &ledit->list_histo, str)) != 0)
			{
				close(fd);
				free(str);
				free(del);
				return (MALLOC_FAIL);
			}
		}
		free(str);
		size_file--;
	}
	close(fd);
	return (SUCCESS);
}

static t_err	nb_line_histo(int *fd_file, char *str, int flags)
{
	int		i;
	int		ret;
	char	buf[2];

	i = 0;
	ft_bzero(buf, sizeof(char) * 1);
	while ((ret = read(*fd_file, buf, 1)) > 0)
	{
		if (buf[0] == '	' || buf[0] < 0 || buf[0] > 127)
		{
			close(*fd_file);
			free(str);
			return (ERROR_CHARAC);
		}
		if (buf[0] == '\n')
			i++;
		ft_bzero(buf, sizeof(char) * 1);
	}
	close(*fd_file);
	if (open(str, flags) == -1)
	{
		free(str);
		return (-1);
	}
	return (i);
}

static t_err	replace_file(char *str, t_listhisto **lst)
{
	int			fd_file;
	t_listhisto	*tmp;

	tmp = (*lst);
	if ((fd_file = open(str, \
			O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
	{
		ft_putendl("21sh:  : can't open fail");
		free(str);
		return (-1);
	}
	ftruncate(fd_file, 0); // use O_TRUNC
	while (tmp && tmp->prev)
		tmp = tmp->prev;
	while (tmp)
	{
		write(fd_file, tmp->line, ft_strlen(tmp->line));
		write(fd_file, "\n", 1);
		tmp = tmp->next;
	}
	close(fd_file);
	return (SUCCESS);
}

t_err			initialize_list_histo(t_mini *shell, \
				t_le *ledit, t_listhisto **lst)
{
	int		fd_file;
	char	*str;
	int		size_file;
	int		ret;

	if ((ret = recup_home(shell, &str)) == USAGE)
		return (SUCCESS);
	else if (ret == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if ((str = ft_strjoinfree(str, "/.21sh_history", 1)) == NULL)
		return (MALLOC_FAIL);
	if ((fd_file = open_file_histo(str, O_RDONLY)) == -1)
		return (SUCCESS);
	else
	{
		if ((size_file = nb_line_histo(&fd_file, str, O_RDONLY)) < 0)
			return (size_file);
		if ((fill_list_histo(ledit, fd_file, size_file, str)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		if (size_file > 250)
			replace_file(str, lst);
		free(str);
	}
	return (SUCCESS);
}
