/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 17:53:01 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/13 11:13:26 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static t_err	opt_cd(char **args, int *i_tab, int *opt)
{
	int		j;

	j = 0;
	while (args[*i_tab])
	{
		if (args[*i_tab][j++] == '-' && args[*i_tab][j])
		{
			while (args[*i_tab][j])
			{
				if (args[*i_tab][j] == 'P')
					*opt = 1;
				else if (args[*i_tab][j] == 'L')
					*opt = 0;
				else
					return (invalid_opt_cd(args[*i_tab][j]));
				j++;
			}
		}
		else
			return (0);
		(*i_tab)++;
		j = 0;
	}
	return (0);
}

static t_err	cd_get_arg(t_mini *shell, char *arg, char **dir)
{
	int		ret;

	ret = 0;
	if (!arg && (ret = recup_home(shell, dir)) < 0)
	{
		if (ret == USAGE)
			ft_putendl_fd("cd: HOME is not set", 2);
		return (ret);
	}
	else if (!arg && ret == 0)
		return (SUCCESS);
	else if (ft_strcmp(arg, "-") == 0 && (ret = recup_old_pwd(shell, dir)) < 0)
	{
		if (ret == USAGE)
			ft_putendl_fd("cd: OLDPWD is not set", 2);
		return (ret);
	}
	else if (ft_strcmp(arg, "-") == 0 && ret == 0)
		return (SUCCESS);
	else if (arg)
	{
		if ((*dir = ft_strdup(arg)) == NULL)
			return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

static int		remove_last_dir(char **str)
{
	int		slash;
	int		i;
	int		len;
	int		ret;

	ret = 0;
	len = (int)ft_strlen(*str) - 1;
	i = 0;
	slash = 0;
	while (len > 0 && (*str)[len] == '/')
		(*str)[len--] = '\0';
	while ((*str)[i])
	{
		if ((*str)[i] == '/')
			slash = i;
		i++;
	}
	if (slash > 0)
	{
		if (ft_strcmp("..", (*str) + slash + 1) == 0)
			ret = 1;
		while (len >= slash)
			(*str)[len--] = '\0';
	}
	return (ret ? remove_last_dir(str) : 0);
}

static int		check_dot_dot(char **str, int i, int slash)
{
	int		len;

	len = (int)ft_strlen(*str) - 1;
	if (len <= 1)
		return (0);
	if ((*str)[len] == '/')
		(*str)[len--] = '\0';
	while ((*str)[i])
	{
		if ((*str)[i] == '/')
			slash = i;
		i++;
	}
	if ((*str)[slash + 1])
	{
		if (ft_strcmp(((*str) + slash + 1), "..") == 0 \
		|| ft_strcmp(((*str) + slash + 1), ".") == 0)
		{
			(*str)[slash] = '\0';
			remove_last_dir(str);
		}
	}
	return (0);
}

t_err			builtin_cd(t_mini *shell)
{
	char	*dir;
	char	*fullpath;
	int		ret;
	int		opt;
	int		index_tab;

	index_tab = 1;
	dir = NULL;
	fullpath = NULL;
	opt = 0;
	if (opt_cd(shell->tab_argv_split, &index_tab, &opt) == USAGE)
		return (USAGE);
	if ((ret = cd_get_arg(shell, shell->tab_argv_split[index_tab], &dir)) < 0)
		return (ret);
	if ((ret = cd_get_fullpath(shell, dir, &fullpath)) < 0)
	{
		free(dir);
		return (ret);
	}
	check_dot_dot(&fullpath, 0, 0);
	if (exchange_directory(opt ? dir : fullpath, shell, opt))
		ret = check_access(opt ? dir : fullpath);
	free(fullpath);
	free(dir);
	return (ret);
}
