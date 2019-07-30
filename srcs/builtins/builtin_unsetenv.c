/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 16:17:35 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/25 19:02:06 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static void	check_for_free_one_env2(t_mini *shell, t_listenv **tmp)
{
	t_listenv	*list;
	t_listenv	*next_mail;

	list = (*tmp);
	next_mail = list->next;
	(void)shell;
	while (next_mail->next)
	{
		next_mail = next_mail->next;
		list = list->next;
	}
	free(next_mail->str_env);
	free(next_mail);
	list->next = NULL;
}

static void	check_for_free_one_env(t_mini *shell, int i, int c, t_listenv **tmp)
{
	t_listenv	*list;
	t_listenv	*next_mail;

	list = (*tmp);
	next_mail = list->next;
	if (c == 1)
	{
		free(list->str_env);
		free(list);
		(*tmp) = next_mail;
	}
	else if (c > 1 && c < shell->nb_mail)
	{
		while (i < (c - 1))
		{
			next_mail = next_mail->next;
			list = list->next;
			i++;
		}
		list->next = next_mail->next;
		free(next_mail->str_env);
		free(next_mail);
	}
	else
		check_for_free_one_env2(shell, tmp);
}

void		delete_on_list_env(t_mini *shell, t_listenv **list, char *str)
{
	t_listenv	*tmp;
	int			i;
	int			s;
	int			c;

	c = 1;
	tmp = (*list);
	i = ft_strlen(str);
	s = 0;
	count_nb_mail(shell, 0, list);
	while (tmp)
	{
		s = ft_strclen(tmp->str_env, '=');
		if (s == i && ft_strncmp(tmp->str_env, str, i) == 0)
		{
			if (!(ft_strncmp("PATH", str, i)))
				shell->no_path = 1;
			check_for_free_one_env(shell, 1, c, list);
			return ;
		}
		c++;
		tmp = tmp->next;
	}
}

t_err		builtin_unsetenv(t_mini *shell)
{
	t_listenv	*list;
	int			ret;

	list = shell->list_env;
	if ((ret = check_nb_arg_unset(shell->nb_arg)) < 0)
		return (ret);
	if (!list)
		return (SUCCESS);
	delete_on_list_env(shell, &shell->list_env, shell->tab_argv_split[1]);
	return (SUCCESS);
}

void		unsetenv_via_env(t_mini *shell, t_env *envs, int *x)
{
	t_listenv	*list;

	list = envs->copy_list_env;
	if (!list)
		return ;
	delete_on_list_env(shell, &envs->copy_list_env, shell->tab_argv_split[*x]);
}
