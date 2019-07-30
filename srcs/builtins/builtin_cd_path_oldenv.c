/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_path_oldenv.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 16:58:45 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/13 11:15:06 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static t_err	add_env_about_cd(t_mini *shell, char *var, char *value)
{
	char	*tmp;
	int		len_var;

	len_var = ft_strlen(var) - 1;
	tmp = NULL;
	if ((tmp = ft_strjoin(var, value)) == NULL)
		return (MALLOC_FAIL);
	else
	{
		if ((check_same_var_env(&shell->list_env, tmp, len_var)) < 0)
		{
			free(tmp);
			return (MALLOC_FAIL);
		}
		if ((check_same_var_env(&shell->list_set, tmp, len_var)) < 0)
		{
			free(tmp);
			return (MALLOC_FAIL);
		}
		free(tmp);
	}
	return (SUCCESS);
}

t_err			exchange_directory(char *dir, t_mini *shell, int opt)
{
	char	buffer[512];

	ft_bzero(buffer, sizeof(char) * 512);
	getcwd(buffer, 512);
	if (opt && !chdir(dir))
	{
		add_env_about_cd(shell, "OLDPWD=", buffer);
		ft_bzero(buffer, sizeof(char) * 512);
		getcwd(buffer, 512);
		add_env_about_cd(shell, "PWD=", buffer);
	}
	else if (!chdir(dir))
	{
		add_env_about_cd(shell, "OLDPWD=", buffer);
		add_env_about_cd(shell, "PWD=", dir);
	}
	else
		return (1);
	return (SUCCESS);
}
