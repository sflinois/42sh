/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_histo_file_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 09:23:51 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 11:53:42 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			recup_int_param(t_listenv **lst, char *str)
{
	t_listenv	*tmp;
	int			len_str;
	int			ret;

	ret = -1;
	tmp = (*lst);
	len_str = ft_strlen(str);
	while (tmp)
	{
		if ((ft_strncmp(tmp->str_env, str, len_str)) == 0)
		{
			if (tmp->str_env[len_str])
				return (ret = protect_atoi(tmp->str_env + len_str, 0));
			else
				return (ret);
		}
		tmp = tmp->next;
	}
	return (ret);
}

char		*recup_str_param(t_listenv **lst, char *str)
{
	t_listenv	*tmp;
	int			len_str;

	tmp = (*lst);
	len_str = ft_strlen(str);
	while (tmp)
	{
		if ((ft_strncmp(tmp->str_env, str, len_str)) == 0)
		{
			if (tmp->str_env[len_str])
				return (ft_strdup(tmp->str_env + len_str));
			else
				return (NULL);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

t_err		fill_file(t_listhisto **lst, int fd_file, int size_max)
{
	t_listhisto		*tmp;
	int				i;

	i = 0;
	tmp = (*lst);
	ftruncate(fd_file, 0);
	while (tmp && tmp->prev && size_max > i)
	{
		if (i != 0)
			i++;
		tmp = tmp->prev;
	}
	while (tmp && size_max > 0)
	{
		write(fd_file, tmp->line, ft_strlen(tmp->line));
		write(fd_file, "\n", 1);
		tmp = tmp->next;
		size_max--;
	}
	close(fd_file);
	return (SUCCESS);
}

t_err		edit_file_histo(t_mini *shell, t_le *ledit)
{
	int		size_max;
	int		fd_file;
	char	*file;

	file = NULL;
	size_max = -1;
	(void)ledit;
	if ((file = recup_str_param(&shell->list_set, "HISTFILE=")) == NULL)
		return (SUCCESS);
	if ((size_max = recup_int_param(&shell->list_set, "HISTFILESIZE=")) == -1)
	{
		free(file);
		return (SUCCESS);
	}
	if ((fd_file = open(file, \
			O_WRONLY | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR)) == -1)
	{
		free(file);
		return (print_fail_open(file));
	}
	free(file);
	fill_file(&ledit->list_histo, fd_file, size_max);
	return (SUCCESS);
}
