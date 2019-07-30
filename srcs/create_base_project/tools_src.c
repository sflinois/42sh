/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_src.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 13:50:43 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/31 14:59:23 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "ft_lineedit.h"

char	*str_keep_until_equal(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			str[i] = '\0';
			return (str);
		}
		i++;
	}
	return (str);
}

char	**transfere_list_to_tab(char **tabb, t_listenv **list, int a)
{
	t_listenv	*tmp;

	tmp = (*list);
	while (tmp)
	{
		tmp = tmp->next;
		a++;
	}
	tmp = (*list);
	if ((tabb = (char**)malloc(sizeof(char*) * (a + 1))) == NULL)
		return (NULL);
	a = 0;
	while (tmp)
	{
		if ((tabb[a] = ft_strdup(tmp->str_env)) == NULL)
		{
			ft_free_tab(tabb);
			return (NULL);
		}
		a++;
		tmp = tmp->next;
	}
	tabb[a] = NULL;
	return (tabb);
}
