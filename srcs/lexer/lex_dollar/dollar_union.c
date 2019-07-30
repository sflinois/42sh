/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_union.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:33:44 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:31:19 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	last_brace(t_le *ledit, int *i)
{
	while (ledit->buffer[*i] && ledit->buffer[*i] != '}')
		(*i)++;
	while (ledit->buffer[*i] && ledit->buffer[*i] == '}')
		(*i)++;
}

int		last_brace_simple_dollar(t_mini *shell, t_le *ledit, int *i, int exist)
{
	last_brace(ledit, i);
	return (simple_dollar(&shell->list_set, ledit, i, exist));
}

void	keep_second_arg(t_le *ledit, int *i)
{
	cut_expansion_dollar(ledit, i);
	while (ledit->buffer[*i] && ledit->buffer[*i] != '}')
		(*i)++;
	ledit->start_cut = (*i);
	(*i)++;
	cut_expansion_dollar(ledit, i);
}

int		dollar_union(t_mini *shell, t_le *ledit, int *i, int exist)
{
	int		save;
	int		save_index;

	save = ledit->start_cut;
	(*i) = (*i) + 2;
	save_index = (*i);
	if (exist == -1 && ledit->buffer[*i] == '$' \
			&& ledit->buffer[(*i) + 1] == '{')
	{
		if ((transforme_expansion(shell, ledit, i)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		(*i) = save_index;
		ledit->start_cut = save;
	}
	if (exist != -1 || ledit->buffer[*i] == '}')
	{
		return (last_brace_simple_dollar(shell, ledit, i, exist));
	}
	else
		keep_second_arg(ledit, i);
	return (0);
}
