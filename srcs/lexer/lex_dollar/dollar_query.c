/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_query.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:17:45 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:51:00 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int				recup_first_arg(t_le *ledit, char **tmp, int *i)
{
	int		len;

	len = (*i) - (ledit->start_cut);
	if ((*tmp = ft_strsub(ledit->buffer, ledit->start_cut, len, 0)) == NULL)
		return (MALLOC_FAIL);
	(*i) = (*i) + 2;
	cut_expansion_dollar(ledit, i);
	return (0);
}

static int		recup_second_arg(t_le *ledit, char **tmp, int *i, int len)
{
	char	*value;

	value = NULL;
	while (ledit->buffer[(*i)] != '}')
	{
		(*i)++;
		len++;
	}
	if (ledit->buffer[(*i)] == '}')
	{
		(*i)++;
		len++;
	}
	if (len == 0)
		param_null_not_set(*tmp);
	else
	{
		if ((value = ft_strsub(ledit->buffer, ledit->start_cut, len, 0)) \
				== NULL)
			return (MALLOC_FAIL);
		param_null_with_arg(*tmp, value);
		free(value);
	}
	return (0);
}

int				dollar_query(t_mini *shell, t_le *ledit, int *i, int exist)
{
	char	*tmp;

	tmp = NULL;
	if (exist != -1)
	{
		return (last_brace_simple_dollar(shell, ledit, i, exist));
	}
	else
	{
		if ((recup_first_arg(ledit, &tmp, i)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		if ((recup_second_arg(ledit, &tmp, i, 0)) == MALLOC_FAIL)
		{
			free(tmp);
			return (MALLOC_FAIL);
		}
		free(tmp);
		(*i)++;
		cut_expansion_dollar(ledit, i);
		ft_bzero(ledit->buffer, sizeof(char) * 2048);
		(*i) = 0;
	}
	return (0);
}
