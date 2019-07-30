/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_tab_func_create_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 17:17:21 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 17:10:16 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void		free_list_completion(t_comp **comp)
{
	t_comp	*next_mail;
	t_comp	*list;

	list = (*comp);
	next_mail = NULL;
	if (!list)
		return ;
	while (list->prev)
		list = list->prev;
	while (list)
	{
		next_mail = list->next;
		if (list->line != NULL)
			free(list->line);
		free(list);
		list = next_mail;
	}
	(*comp) = NULL;
}

static int	create_list_completion(t_comp **comp, char *str)
{
	if (((*comp) = (t_comp*)malloc(sizeof(t_comp))) == NULL)
		return (MALLOC_FAIL);
	ft_bzero((*comp), sizeof(t_comp));
	(*comp)->next = NULL;
	(*comp)->prev = NULL;
	if (str)
	{
		if (((*comp)->line = ft_strdup(str)) == NULL)
		{
			free((*comp));
			return (MALLOC_FAIL);
		}
	}
	(*comp)->len_line = ft_strlen(str);
	(*comp)->max_len = (*comp)->len_line;
	return (SUCCESS);
}

static int	add_mail_list_completion(t_comp **comp, char *str)
{
	t_comp	*tmp;

	if ((tmp = (t_comp*)malloc(sizeof(t_comp))) == NULL)
		return (MALLOC_FAIL);
	ft_bzero(tmp, sizeof(t_comp));
	if ((tmp->line = ft_strdup(str)) == NULL)
	{
		free(tmp);
		return (MALLOC_FAIL);
	}
	while ((*comp) && (*comp)->next)
		(*comp) = (*comp)->next;
	tmp->next = NULL;
	(*comp)->next = tmp;
	tmp->prev = (*comp);
	(*comp) = tmp;
	(*comp)->len_line = ft_strlen(str);
	(*comp)->max_len = (*comp)->prev->max_len;
	if ((*comp)->len_line > (*comp)->max_len)
	{
		(*comp)->prev->max_len = (*comp)->len_line;
		(*comp)->max_len = (*comp)->len_line;
	}
	return (SUCCESS);
}

int			add_to_list_completion(t_comp **comp, char *str)
{
	if (*comp == NULL)
	{
		if ((create_list_completion(comp, str)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	else
	{
		if ((add_mail_list_completion(comp, str)) == MALLOC_FAIL)
		{
			free_list_completion(comp);
			return (MALLOC_FAIL);
		}
	}
	return (SUCCESS);
}
