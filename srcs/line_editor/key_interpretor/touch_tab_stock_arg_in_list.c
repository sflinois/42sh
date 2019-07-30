/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_tab_stock_arg_in_list.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 15:49:15 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 17:56:18 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

static int	compare_dname_and_str(t_comp **comp, char *name, char *str, int len)
{
	if (len != 0)
	{
		if (ft_strncmp(name, str, len) == 0 && ft_strncmp(name, ".", 1))
		{
			if (add_to_list_completion(comp, name) == MALLOC_FAIL)
				return (MALLOC_FAIL);
			return (1);
		}
	}
	else
	{
		if ((ft_strncmp(name, ".", 1)) != 0)
		{
			if (add_to_list_completion(comp, name) == MALLOC_FAIL)
				return (MALLOC_FAIL);
			return (1);
		}
	}
	return (SUCCESS);
}

int			stock_binary(char *dir, char *str, int size, t_comp **comp)
{
	DIR				*rep;
	struct dirent	*fichier_lu;
	int				ret;

	ret = 0;
	if (dir == NULL)
	{
		if ((dir = ft_strdup(".")) == NULL)
			return (MALLOC_FAIL);
	}
	if ((rep = opendir(dir)) != NULL)
	{
		while ((fichier_lu = readdir(rep)) != NULL)
		{
			if ((ret = compare_dname_and_str(comp, fichier_lu->d_name, \
			str, size)) == MALLOC_FAIL)
				return (MALLOC_FAIL);
			if (ret == 1)
				if ((add_color_file(*comp, dir, &ret)) == MALLOC_FAIL)
					return (MALLOC_FAIL);
		}
		if ((closedir(rep)) == -1)
			ft_putendl_fd("21sh: close: error close directory", 2);
	}
	return (SUCCESS);
}

static int	stock_builtin(char *str, int size, int i, t_comp **comp)
{
	static struct s_pr_built	tab_built[12] = {
		{"echo"},
		{"cd"},
		{"setenv"},
		{"unsetenv"},
		{"env"},
		{"exit"},
		{"history"},
		{"set"},
		{"unset"},
		{"export"},
		{"fg"},
		{"bg"},
	};

	while (i < 12)
	{
		if (compare_dname_and_str(comp, tab_built[i].arg_built, str, size) \
		== MALLOC_FAIL)
			return (MALLOC_FAIL);
		i++;
	}
	return (SUCCESS);
}

int			stock_arg_for_cmd(t_mini *shell, char *str, int size, t_comp **comp)
{
	int		i;

	i = 0;
	if (shell->tab_env)
	{
		while (shell->tab_env[i])
		{
			if ((stock_binary(shell->tab_env[i++], str, size, comp)) \
			== MALLOC_FAIL)
				return (MALLOC_FAIL);
			i++;
		}
	}
	if ((stock_builtin(str, size, 0, comp)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

int			stock_var_set(t_listenv **lst, char *str, int size, t_comp **comp)
{
	t_listenv	*tmp;

	tmp = (*lst);
	while (tmp)
	{
		if (size != 0)
		{
			if (ft_strncmp(tmp->str_env, str, size) == 0)
			{
				if (add_to_list_completion(comp, \
					str_keep_until_equal(tmp->str_env)) == MALLOC_FAIL)
					return (MALLOC_FAIL);
			}
		}
		else
		{
			if (add_to_list_completion(comp, \
				str_keep_until_equal(tmp->str_env)) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}
