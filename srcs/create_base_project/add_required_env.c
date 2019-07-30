/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_required_env.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 15:28:41 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 09:19:14 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static t_err	recup_pwd(t_mini *shell, t_listenv **lst)
{
	char	buffer[512];
	char	*str;
	int		ret;

	ret = SUCCESS;
	ft_bzero(buffer, sizeof(char) * 513);
	getcwd(buffer, 513);
	if ((str = ft_strjoin("PWD=", buffer)) == NULL)
		return (MALLOC_FAIL);
	if ((add_on_list_env(shell, lst, str, 0)) == MALLOC_FAIL)
		ret = MALLOC_FAIL;
	free(str);
	return (ret);
}

static int		find_variable_on_list(t_listenv **list, char *str)
{
	t_listenv	*tmp;

	tmp = (*list);
	if (!tmp)
		return (-1);
	while (tmp)
	{
		if ((ft_strncmp(tmp->str_env, str, ft_strlen(str))) == 0)
			return (1);
		tmp = tmp->next;
	}
	return (-1);
}

static void		add_one_to_shlvl(t_listenv **list)
{
	t_listenv	*tmp;

	tmp = (*list);
	while (tmp)
	{
		if ((ft_strncmp(tmp->str_env, "SHLVL=", 6)) == 0)
		{
			if (tmp->str_env[6] <= '8')
				tmp->str_env[6] = tmp->str_env[6] + 1;
			return ;
		}
		tmp = tmp->next;
	}
}

t_err			verif_required_env(t_mini *shell, t_listenv **tmp)
{
	int		ret;

	ret = SUCCESS;
	if ((find_variable_on_list(tmp, "PWD=")) == -1)
		if ((recup_pwd(shell, tmp)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	if ((find_variable_on_list(tmp, "SHLVL=")) == 1)
		add_one_to_shlvl(tmp);
	else
	{
		if ((add_on_list_env(shell, tmp, "SHLVL=1", 0)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	if ((find_variable_on_list(tmp, "_=")) == -1)
		if ((add_on_list_env(shell, tmp, "_=/usr/bin/env", 0)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	return (SUCCESS);
}
