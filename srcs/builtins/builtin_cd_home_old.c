/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_home_old.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 10:50:04 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/30 14:37:25 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

int				set_or_not(t_listenv **lst, char *to_find, \
				int int_or_str, char **copy)
{
	t_listenv	*tmp;
	int			len;

	len = ft_strlen(to_find);
	tmp = (*lst);
	while (tmp)
	{
		if (ft_strncmp(tmp->str_env, to_find, len) == 0)
		{
			if (tmp->str_env[len])
			{
				if (int_or_str == 0)
					return (1);
				else
				{
					if ((*copy = ft_strdup(tmp->str_env + len)) == NULL)
						return (MALLOC_FAIL);
				}
			}
			else
				return (-1);
		}
		tmp = tmp->next;
	}
	return (-1);
}

t_err			recup_home(t_mini *minishell, char **str)
{
	t_listenv	*tmp;

	tmp = minishell->list_env;
	while (tmp)
	{
		if ((ft_strncmp(tmp->str_env, "HOME", 4)) == 0)
		{
			if (tmp->str_env[5])
			{
				if (((*str) = ft_strdup(tmp->str_env + 5)) == NULL)
					return (MALLOC_FAIL);
				else
					return (SUCCESS);
			}
			else if (tmp->str_env[5] == '\0')
				return (USAGE);
		}
		tmp = tmp->next;
	}
	return (USAGE);
}

t_err			recup_old_pwd(t_mini *minishell, char **str)
{
	t_listenv	*tmp;

	tmp = minishell->list_env;
	while (tmp)
	{
		if ((ft_strncmp(tmp->str_env, "OLDPWD=", 7)) == 0)
		{
			if (tmp->str_env[7])
			{
				if (((*str) = ft_strdup(tmp->str_env + 7)) == NULL)
					return (MALLOC_FAIL);
				else
				{
					ft_putendl(tmp->str_env + 8);
					return (SUCCESS);
				}
			}
			else if (tmp->str_env[8] == '\0')
			{
				return (USAGE);
			}
		}
		tmp = tmp->next;
	}
	return (USAGE);
}

static t_err	get_fullpath(t_mini *shell, char *dir, char **fullpath)
{
	char	buff[520];

	ft_bzero(buff, sizeof(char) * 520);
	getcwd(buff, 520);
	if (set_or_not(&shell->list_env, "PWD=", 0, NULL) == -1)
	{
		if ((*fullpath = ft_strdup(buff)) == NULL)
			return (MALLOC_FAIL);
	}
	else
	{
		if ((set_or_not(&shell->list_env, "PWD=", 1, fullpath)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	if ((*fullpath = ft_strjoinfree(*fullpath, "/", 1)) == NULL)
		return (MALLOC_FAIL);
	if ((*fullpath = ft_strjoinfree(*fullpath, dir, 1)) == NULL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

t_err			cd_get_fullpath(t_mini *shell, char *dir, char **fullpath)
{
	if (dir && dir[0] != '/')
	{
		if ((get_fullpath(shell, dir, fullpath)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	else if (dir)
	{
		if ((*fullpath = ft_strdup(dir)) == NULL)
			return (MALLOC_FAIL);
	}
	else
	{
		if ((*fullpath = ft_strdup("")) == NULL)
			return (MALLOC_FAIL);
	}
	return (SUCCESS);
}
