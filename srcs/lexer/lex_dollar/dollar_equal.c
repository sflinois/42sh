/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_equal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 14:57:30 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:11:53 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	check_second_arg(t_mini *shell, t_le *ledit, int *i, char **param)
{
	char	*value;
	int		len;

	len = 0;
	value = NULL;
	while ((*i) < (int)ft_strlen(ledit->buffer) && ledit->buffer[*i] != '}')
	{
		(*i)++;
		len++;
	}
	if (len == 0)
	{
		if ((add_on_list_env(shell, &shell->list_set, *param, 0)) \
				== MALLOC_FAIL)
			return (MALLOC_FAIL);
		return (0);
	}
	if ((value = ft_strsub(ledit->buffer, ((*i) - len), len, 0)) == NULL)
		return (MALLOC_FAIL);
	if ((*param = ft_strjoinfree(*param, value, 3)) == NULL)
		return (MALLOC_FAIL);
	if ((add_on_list_env(shell, &shell->list_set, *param, 0)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

static int	check_first_arg(t_mini *shell, t_le *ledit, int *i, char **tmp)
{
	if (if_param_exist(&shell->list_set, *tmp, 0, ft_strclen(*tmp, '=')) == -1)
	{
		if ((check_second_arg(shell, ledit, i, tmp)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	free(*tmp);
	ledit->start_cut = (*i);
	while (ledit->buffer[*i] == '}')
		(*i)++;
	cut_expansion_dollar(ledit, i);
	return (SUCCESS);
}

int			param_null(t_le *ledit, char **tmp, int *i)
{
	if ((recup_first_arg(ledit, tmp, i)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if ((*tmp = ft_strjoinfree(*tmp, "=", 1)) == NULL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

int			dollar_equal(t_mini *shell, t_le *ledit, int *i, int exist)
{
	char	*tmp;
	int		save_index;

	tmp = NULL;
	if (exist == -1)
	{
		if ((param_null(ledit, &tmp, i)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		if (ledit->buffer[*i] == '$' && ledit->buffer[(*i) + 1] == '{')
		{
			save_index = (*i);
			if ((transforme_expansion(shell, ledit, i)) == MALLOC_FAIL)
				return (MALLOC_FAIL);
			(*i) = save_index;
		}
		return (check_first_arg(shell, ledit, i, &tmp));
	}
	last_brace_simple_dollar(shell, ledit, i, exist);
	return (0);
}
