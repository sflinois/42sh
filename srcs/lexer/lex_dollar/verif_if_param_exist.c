/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_if_param_exist.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 10:26:11 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:43:41 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int			if_param_exist(t_listenv **lst, char *buffer, int i, int j)
{
	t_listenv	*tmp;
	int			index_mail;

	index_mail = 0;
	tmp = (*lst);
	while (tmp)
	{
		if (tmp->str_env[j] && tmp->str_env[j] == '=' \
		&& ft_strncmp(tmp->str_env, buffer + i, j) == 0)
		{
			if (tmp->str_env[j + 1] == '\0')
				return (-1);
			return (index_mail);
		}
		tmp = tmp->next;
		index_mail++;
	}
	return (-1);
}

static int	check_which_expansion(t_mini *shell, t_le *ledit, int *i, int exist)
{
	int		ret;

	ret = 0;
	if (ledit->buffer[*i] == '}')
		ret = simple_dollar(&shell->list_set, ledit, i, exist);
	else if (ledit->buffer[*i] == ':' && ledit->buffer[(*i) + 1] == '-')
		ret = dollar_union(shell, ledit, i, exist);
	else if (ledit->buffer[*i] == ':' && ledit->buffer[(*i) + 1] == '=')
		ret = dollar_equal(shell, ledit, i, exist);
	else if (ledit->buffer[*i] == ':' && ledit->buffer[(*i) + 1] == '?')
		ret = dollar_query(shell, ledit, i, exist);
	else if (ledit->buffer[*i] == ':' && ledit->buffer[(*i) + 1] == '+')
		ret = dollar_add(shell, ledit, i, exist);
	else if (ledit->buffer[*i] == '%' && ledit->buffer[(*i) + 1] == '}')
		ret = dollar_percent(shell, ledit, i, exist);
	else if (ledit->buffer[*i] == '%' && ledit->buffer[(*i) + 1] == '%')
		ret = dollar_double_percent(shell, ledit, i, exist);
	else if (ledit->buffer[*i] == '#' && ledit->buffer[(*i) + 1] == '}')
		ret = dollar_diez(shell, ledit, i, exist);
	else if (ledit->buffer[*i] == '#' && ledit->buffer[(*i) + 1] == '#')
		ret = dollar_double_diez(shell, ledit, i, exist);
	return (ret);
}

int			browse_param(t_mini *shell, t_le *ledit, int *i)
{
	int		j;
	int		exist;

	j = (*i);
	while (ledit->buffer[j] && if_alpha_or_digit(ledit->buffer[j]) == 1)
		j++;
	j = j - (*i);
	exist = if_param_exist(&shell->list_set, ledit->buffer, *i, j);
	(*i) = (*i) + j;
	return (check_which_expansion(shell, ledit, i, exist));
}
