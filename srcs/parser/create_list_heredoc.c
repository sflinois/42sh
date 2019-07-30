/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:25:20 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 13:24:29 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			transfere_list(t_listenv **final, t_list_eof **tmp)
{
	t_listenv	*dst;
	t_list_eof	*src;

	dst = (*final);
	src = (*tmp);
	if (!src)
		return (0);
	else
	{
		if ((create_list_for_setenv(final, src->str_arg)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		src = src->next;
	}
	while (src)
	{
		if ((add_to_list(final, src->str_arg)) == MALLOC_FAIL)
		{
			free_list_shell(final);
			return (MALLOC_FAIL);
		}
		src = src->next;
	}
	free_list_heredoc(tmp);
	return (0);
}

static int	add_to_list_heredoc(t_list_eof **list, char *str)
{
	t_list_eof	*tmp;
	t_list_eof	*tmp1;

	if ((tmp1 = (t_list_eof*)malloc(sizeof(t_list_eof))) == NULL)
		return (MALLOC_FAIL);
	ft_bzero(tmp1, sizeof(tmp1));
	if (str != NULL)
	{
		if ((tmp1->str_arg = ft_strdup(str)) == NULL)
		{
			free(tmp1);
			return (MALLOC_FAIL);
		}
	}
	else
		tmp1->str_arg = NULL;
	tmp = (*list);
	if (tmp && tmp1)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = tmp1;
		tmp1->next = NULL;
	}
	return (0);
}

static int	create_list_for_heredoc(t_list_eof **tmp, char *str)
{
	t_list_eof	*list;

	if ((list = (t_list_eof*)malloc(sizeof(t_list_eof))) == NULL)
		return (MALLOC_FAIL);
	ft_bzero(list, sizeof(t_list_eof));
	(*tmp) = list;
	list->next = NULL;
	if (str != NULL)
	{
		if ((list->str_arg = ft_strdup(str)) == NULL)
		{
			free(list);
			list = NULL;
			return (MALLOC_FAIL);
		}
	}
	else if (str == NULL)
		list->str_arg = NULL;
	return (0);
}

int			create_list_heredoc(char *str, t_le *ledit)
{
	int		ret;

	ret = 0;
	if (!(ledit->list_heredoc))
		ret = create_list_for_heredoc(&ledit->list_heredoc, str);
	else
		ret = add_to_list_heredoc(&ledit->list_heredoc, str);
	if (str)
		free(str);
	return (ret);
}
