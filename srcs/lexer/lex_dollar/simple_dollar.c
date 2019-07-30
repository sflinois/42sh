/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 11:09:07 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:35:09 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		simple_dollar(t_listenv **lst, t_le *ledit, int *i, int exist)
{
	t_listenv	*tmp;
	int			j;

	tmp = (*lst);
	(*i)++;
	cut_expansion_dollar(ledit, i);
	if (exist == -1)
		return (0);
	while (tmp && exist > 0)
	{
		tmp = tmp->next;
		exist--;
	}
	if (exist == 0)
	{
		j = ft_strclen(tmp->str_env, '=') + 1;
		if (tmp->str_env[j] == '\0')
			return (0);
		while (tmp->str_env[j])
		{
			inser_on_buffer(ledit, tmp->str_env + j++);
			(*i)++;
		}
	}
	return (0);
}
