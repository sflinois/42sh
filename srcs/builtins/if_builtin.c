/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:06:56 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:19:25 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static int	go_builtins(t_mini *shell, char *str)
{
	int						i;
	static struct s_buil	tab_built[16] = {
		{"echo", &builtin_echo},
		{"cd", &builtin_cd},
		{"setenv", &builtin_setenv},
		{"unsetenv", &builtin_unsetenv},
		{"env", &builtin_env},
		{"exit", &builtin_exit},
		{"history", &builtin_history},
		{"set", &builtin_set},
		{"unset", &builtin_unset},
		{"export", &builtin_export},
		{"fg", &builtin_fg},
		{"bg", &builtin_bg},
		{"jobs", &builtin_jobs},
		{"hash", &builtin_hash},
		{"alias", &builtin_alias},
		{"unalias", &builtin_unalias}
	};

	i = 0;
	while (i < 16)
		if ((ft_strcmp(tab_built[i++].arg_built, str)) == 0)
			return (tab_built[i - 1].fct(shell));
	return (-4);
}

void		count_nb_mail(t_mini *shell, int i, t_listenv **lst)
{
	t_listenv	*tmp;

	tmp = (*lst);
	if (!tmp)
		return ;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	shell->nb_mail = i;
}

int			check_builtin(t_mini *shell, char **tabb)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	count_nb_mail(shell, 0, &shell->list_env);
	if ((ret = go_builtins(shell, tabb[0])) != -4)
		return (ret);
	if (ft_strclen(tabb[0], '=') > -1)
		return (check_variable_to_add(shell, tabb));
	return (1);
}
