/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list_stock_line_histo.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/27 15:36:58 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 11:51:08 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include <term.h>

static int	create_list_histo(t_listhisto **list, char *str)
{
	if (((*list) = (t_listhisto*)malloc(sizeof(t_listhisto))) == NULL)
		return (MALLOC_FAIL);
	ft_bzero((*list), sizeof(t_listhisto));
	(*list)->next = NULL;
	(*list)->prev = NULL;
	if (str)
	{
		if (((*list)->line = ft_strdup(str)) == NULL)
		{
			free((*list));
			return (MALLOC_FAIL);
		}
	}
	return (0);
}

static int	add_to_list_history(t_le *ledit, t_listhisto **list, char *str)
{
	t_listhisto	*tmp;

	if ((tmp = (t_listhisto*)malloc(sizeof(t_listhisto))) == NULL)
		return (MALLOC_FAIL);
	ft_bzero(tmp, sizeof(t_listhisto));
	if (str)
	{
		if ((tmp->line = ft_strdup(str)) == NULL)
		{
			free(tmp);
			return (MALLOC_FAIL);
		}
	}
	while ((*list) && (*list)->next)
	{
		(*list) = (*list)->next;
	}
	tmp->next = NULL;
	(*list)->next = tmp;
	tmp->prev = (*list);
	ledit->list_histo = tmp;
	return (0);
}

int			stock_line_for_histo(t_le *ledit, t_listhisto **lst, char *str)
{
	if ((*lst) == NULL)
	{
		if ((create_list_histo(lst, str)) != 0)
			return (MALLOC_FAIL);
	}
	else
	{
		if ((add_to_list_history(ledit, lst, str)) != 0)
		{
			free_list_prev(ledit);
			ledit->list_histo = NULL;
			return (MALLOC_FAIL);
		}
	}
	return (SUCCESS);
}

void		list_to_the_end(t_le *ledit)
{
	while (ledit->list_histo && ledit->list_histo->next)
		ledit->list_histo = ledit->list_histo->next;
}
