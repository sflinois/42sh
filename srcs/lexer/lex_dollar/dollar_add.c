/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:00:37 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:08:33 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		dollar_add(t_mini *shell, t_le *ledit, int *i, int exist)
{
	(*i) = (*i) + 2;
	if (exist == -1)
	{
		return (last_brace_simple_dollar(shell, ledit, i, exist));
	}
	else
	{
		cut_expansion_dollar(ledit, i);
		if (ledit->buffer[*i] == '$' && ledit->buffer[(*i) + 1] == '{')
			transforme_expansion(shell, ledit, i);
		while (ledit->buffer[*i] && ledit->buffer[(*i)] != '}')
			(*i)++;
		ledit->start_cut = (*i);
		while (ledit->buffer[*i] && ledit->buffer[*i] == '}')
			(*i)++;
		cut_expansion_dollar(ledit, i);
	}
	return (0);
}
