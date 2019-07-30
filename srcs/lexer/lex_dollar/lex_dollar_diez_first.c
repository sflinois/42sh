/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_dollar_diez_first.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:19:18 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:33:41 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	replace_result(t_le *ledit, int *i, int rslt)
{
	char	*to_copy;
	int		j;

	j = 0;
	to_copy = NULL;
	(*i)++;
	ledit->index_buffer = (*i);
	cut_expansion_dollar(ledit, i);
	if ((to_copy = ft_itoa(rslt)) == NULL)
		return (MALLOC_FAIL);
	while (to_copy[j])
	{
		inser_on_buffer(ledit, to_copy + j++);
		(*i)++;
	}
	free(to_copy);
	return (SUCCESS);
}

int			browse_dollar_diez(t_listenv **lst, t_le *ledit, int *i)
{
	t_listenv	*tmp;
	int			j;
	int			rslt;

	tmp = (*lst);
	j = 0;
	(*i)++;
	j = (*i);
	rslt = 0;
	while (if_alpha_or_digit(ledit->buffer[j]) == 1)
		j++;
	j = j - (*i);
	(*i) = (*i) + j;
	while (j > 0 && tmp)
	{
		if (ft_strncmp(tmp->str_env, ledit->buffer + ((*i) - j), j) == 0 \
		&& tmp->str_env[j] == '=')
			rslt = ft_strlen(tmp->str_env) - (j + 1);
		tmp = tmp->next;
	}
	if ((replace_result(ledit, i, rslt)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (0);
}
