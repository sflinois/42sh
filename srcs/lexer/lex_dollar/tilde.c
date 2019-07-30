/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 13:27:25 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:37:19 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	recup_value_param(t_listenv **lst, t_le *ledit, int *i, char *param)
{
	t_listenv	*tmp;
	int			j;

	j = ft_strclen(param, '=');
	tmp = (*lst);
	while (tmp)
	{
		if (ft_strncmp(tmp->str_env, param, j) == 0)
		{
			if (tmp->str_env[j + 1])
			{
				j++;
				cut_expansion_dollar(ledit, i);
				while (tmp->str_env[j])
				{
					inser_on_buffer(ledit, tmp->str_env + j++);
					(*i)++;
				}
			}
			else
				return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

int			transforme_tilde(t_mini *shell, t_le *ledit, int *i)
{
	if ((*i) > 0 && ft_strclen("&| ;", ledit->buffer[(*i) - 1]) == -1)
	{
		(*i)++;
		return (0);
	}
	ledit->start_cut = (*i);
	(*i)++;
	if (ledit->buffer[*i] == '\0' || ft_strclen(" /", ledit->buffer[*i]) > -1)
		recup_value_param(&shell->list_env, ledit, i, "HOME=");
	else if (ledit->buffer[*i] == '-')
	{
		(*i)++;
		if (ledit->buffer[*i] == '\0' \
		|| ft_strclen(" /", ledit->buffer[*i]) > -1)
			recup_value_param(&shell->list_env, ledit, i, "OLDPWD=");
	}
	return (0);
}
