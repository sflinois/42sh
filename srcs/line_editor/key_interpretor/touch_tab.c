/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 09:01:36 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 17:54:57 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	stock_arg_comp(t_mini *shell, char *str, int pos, t_comp **comp)
{
	int		size;
	int		ret;

	size = 0;
	ret = 0;
	if (str != NULL)
		size = ft_strlen(str);
	if (pos == 0)
		ret = stock_arg_for_cmd(shell, str, size, comp);
	else if (pos == 1)
	{
		if ((access(str, F_OK | R_OK)) == 0)
		{
			ret = stock_binary(str, NULL, 0, comp);
			if (*comp)
				(*comp)->in_dir = 1;
		}
		else
			ret = stock_binary(".", str, size, comp);
	}
	else if (pos == 2)
		ret = stock_var_set(&shell->list_set, str, size, comp);
	return (ret);
}

static int	get_arg_possible(t_mini *shell, char *str, int pos, t_comp **comp)
{
	int		i;

	i = 1;
	if ((stock_arg_comp(shell, str, pos, comp)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (*comp == NULL)
		return (SUCCESS);
	while ((*comp)->prev)
	{
		(*comp)->prev->max_len = (*comp)->max_len;
		(*comp)->prev->in_dir = (*comp)->in_dir;
		(*comp)->nb_mail = i;
		(*comp)->prev->nb_mail = i + 1;
		i++;
		(*comp) = (*comp)->prev;
	}
	return (SUCCESS);
}

int			touch_tab(t_mini *shell, t_le *ledit, int pos)
{
	char	*str;
	int		ret;
	t_comp	*comp;

	str = NULL;
	comp = NULL;
	ret = SUCCESS;
	if (ledit->buffer[0] == '\0')
		return (0);
	if ((define_arg(ledit, ledit->buffer, &pos, &str)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	ret = get_arg_possible(shell, str, pos, &comp);
	if (ret == SUCCESS && comp)
		ret = print_possibility_comp(ledit, &comp, \
			str == NULL ? 0 : ft_strlen(str));
	if (str)
		free(str);
	return (ret);
}
