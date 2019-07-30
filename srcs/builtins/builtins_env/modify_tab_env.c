/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modify_tab_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:26:38 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/25 19:07:42 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

char	**realloc_tabb(t_mini *shell, int *i, int j, int x)
{
	char	**tabb;

	tabb = NULL;
	if ((tabb = (char**)malloc(sizeof(char*) * \
					shell->nb_arg - (*i) + 1)) == NULL)
		return (NULL);
	j = 0;
	while (shell->tab_argv_split[*i])
	{
		tabb[x] = ft_strdup(shell->tab_argv_split[*i]);
		x++;
		(*i)++;
	}
	tabb[x] = NULL;
	return (tabb);
}

int		regenere_tab_env(t_mini *shell, t_env *envs)
{
	t_listenv	*list;
	char		*str;

	str = NULL;
	list = shell->list_env;
	free_list_shell(&envs->copy_list_env);
	while (list)
	{
		if ((ft_strncmp(list->str_env, "PATH=", 4)) == 0)
		{
			if (list->str_env[5])
			{
				if ((str = ft_strdup(list->str_env + 5)) == NULL)
					return (MALLOC_FAIL);
			}
		}
		list = list->next;
	}
	if ((change_env_and_join_local(shell, str)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

void	remplace_tabb_env(t_mini *shell, char *str, int j)
{
	if (shell->no_path == 0)
		ft_free_tab(shell->tab_env);
	if (str[j + 1])
	{
		shell->tab_env = ft_strsplit(str + (j + 1), ':');
		add_slash_to_tab_env(shell->tab_env);
		shell->no_path = 0;
	}
	else
		shell->no_path = 1;
}

t_err	add_slash_to_tab_env(char **tabb)
{
	int		i;

	i = 0;
	if (!(*tabb))
		return (USAGE);
	while (tabb[i])
	{
		if ((tabb[i] = ft_strjoinfree(tabb[i], "/", 1)) == NULL)
		{
			ft_free_tab(tabb);
			return (MALLOC_FAIL);
		}
		i++;
	}
	return (SUCCESS);
}

t_err	change_env_and_join_local(t_mini *shell, char *str)
{
	if (shell->no_path == 0 && shell->tab_env)
		ft_free_tab(shell->tab_env);
	if (!str)
	{
		if ((str = ft_strdup("/usr/bin:/bin")) == NULL)
			return (MALLOC_FAIL);
	}
	if ((shell->tab_env = ft_strsplit(str, ':')) == NULL)
	{
		free(str);
		return (MALLOC_FAIL);
	}
	shell->no_path = 0;
	if ((add_slash_to_tab_env(shell->tab_env)) == MALLOC_FAIL)
	{
		free(str);
		return (MALLOC_FAIL);
	}
	free(str);
	return (SUCCESS);
}
