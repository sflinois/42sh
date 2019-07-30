/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transforme_expansion.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 17:12:37 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:41:24 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			place_last_return(t_le *ledit, int *i)
{
	char	*tmp;
	int		j;

	j = 0;
	tmp = NULL;
	if ((tmp = ft_itoa(ledit->i_return)) == NULL)
		return (MALLOC_FAIL);
	(*i) += 2;
	cut_expansion_dollar(ledit, i);
	while (tmp[j])
	{
		inser_on_buffer(ledit, tmp + j++);
		(*i)++;
	}
	return (0);
}

static int	browse_dollar(t_mini *shell, t_le *ledit, int *i)
{
	(*i)++;
	if (ledit->buffer[*i] == '{')
	{
		(*i)++;
		if (ledit->buffer[*i] == '#')
		{
			if ((browse_dollar_diez(&shell->list_set, ledit, i)) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		}
		else if (ledit->buffer[*i] == '?')
			return (place_last_return(ledit, i));
		else
		{
			cut_expansion_dollar(ledit, i);
			if ((browse_param(shell, ledit, i)) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		}
	}
	return (0);
}

int			go_next_and_echap(char *buffer, int *i, char c)
{
	while (buffer[*i] && buffer[*i] != c)
	{
		if (buffer[*i] == '\\' && c == '"')
		{
			echap_charac(buffer, *i);
			if (buffer[*i] == c)
				(*i)++;
		}
		else
			(*i)++;
	}
	echap_charac(buffer, *i);
	return (0);
}

int			transforme_expansion(t_mini *shell, t_le *ledit, int *i)
{
	while (ledit->buffer[*i])
	{
		if (ledit->buffer[*i] == '\'' \
				&& if_echap_and(ledit->buffer, *i, 0) == FALSE)
			go_next_same_char(ledit->buffer, i, '\'');
		if (ledit->buffer[*i] == '$' \
				&& if_echap_and(ledit->buffer, *i, 0) == FALSE)
		{
			ledit->start_cut = *i;
			if ((browse_dollar(shell, ledit, i)) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		}
		else if (ledit->buffer[(*i)] == '~' \
				&& if_echap_and(ledit->buffer, *i, 0) == FALSE)
			transforme_tilde(shell, ledit, i);
		else
			(*i)++;
	}
	if ((int)ft_strlen(ledit->buffer) == 0)
		return (EMPTY_BUFF);
	ledit->index_buffer = 0;
	return (0);
}
