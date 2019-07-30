/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tab_path_and_list_env.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 17:28:26 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 09:27:37 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

t_err	recup_env(t_mini *minishell, char **env)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (env[i])
	{
		if ((ft_strncmp(env[i], "PATH=", 4)) == 0)
			if (env[i] + 5)
				str = (env[i] + 5);
		i++;
	}
	if (str == NULL)
		return (change_env_and_join_local(minishell, NULL));
	if ((minishell->tab_env = ft_strsplit(str, ':')) == NULL)
	{
		free(str);
		return (MALLOC_FAIL);
	}
	i = 0;
	if ((add_slash_to_tab_env(minishell->tab_env)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

t_err	add_to_list(t_listenv **list, char *str)
{
	t_listenv	*tmp;
	t_listenv	*tmp1;

	if ((tmp1 = (t_listenv*)malloc(sizeof(t_listenv))) == NULL)
		return (MALLOC_FAIL);
	ft_bzero(tmp1, sizeof(tmp1));
	if (str != NULL)
	{
		if ((tmp1->str_env = ft_strdup(str)) == NULL)
		{
			free(tmp1);
			return (MALLOC_FAIL);
		}
	}
	else
		tmp1->str_env = NULL;
	tmp = (*list);
	if (tmp && tmp1)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = tmp1;
		tmp1->next = NULL;
	}
	return (SUCCESS);
}

t_err	create_list(t_listenv **tmp, char **env, int i)
{
	t_listenv	*list;

	while (env[i])
		i++;
	if (i == 0)
		return (SUCCESS);
	i = 0;
	if ((list = (t_listenv*)malloc(sizeof(t_listenv))) == NULL)
		return (MALLOC_FAIL);
	(*tmp) = list;
	ft_bzero(list, sizeof(t_listenv));
	list->next = NULL;
	if (env[i] != NULL)
		if ((list->str_env = ft_strdup(env[i++])) == NULL)
		{
			free(list);
			return (MALLOC_FAIL);
		}
	while (env[i] != NULL)
		if ((add_to_list(&list, env[i++])) == MALLOC_FAIL)
		{
			free_list_shell(&list);
			return (MALLOC_FAIL);
		}
	return (SUCCESS);
}
