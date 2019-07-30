/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:19:33 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/13 10:53:12 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

t_err	check_access(char *dir)
{
	if (!(access(dir, F_OK)) && access(dir, X_OK))
	{
		ft_putstr("cd");
		ft_putstr(": permission denied: ");
		if (dir)
			ft_putendl(dir);
		return (USAGE);
	}
	else if ((access(dir, F_OK)) == -1)
	{
		ft_putstr("cd");
		ft_putstr(": no such file or directory: ");
		if (dir)
			ft_putendl(dir);
		return (USAGE);
	}
	return (SUCCESS);
}

t_err	put_env_illegal_options(char **tabb, int i)
{
	if (tabb[i][1] == '\0')
		return (SUCCESS);
	else
	{
		ft_putstr_fd("env: illegal option -- ", 2);
		ft_putchar_fd(tabb[i][1], 2);
		ft_putchar_fd('\n', 2);
		ft_putstr_fd("usage: env [-iv] [-P utilpath]", 2);
		ft_putstr_fd("[-S string] [-u name]", 2);
		ft_putstr_fd("           [name=value ...] ", 2);
		ft_putendl_fd("[utility [argument ...]]", 2);
	}
	return (USAGE);
}

t_err	error_no_arg_with_unset(void)
{
	ft_putendl_fd("env: option requires an argument -- u", 2);
	ft_putstr_fd("usage: env [-iv] [-P utilpath] ", 2);
	ft_putstr_fd("[-S string] [-u name]", 2);
	ft_putstr_fd("           [name=value ...]", 2);
	ft_putendl_fd(" [utility [argument ...]]", 2);
	return (USAGE);
}

t_err	print_error_write_equal_env(char **tabb, int options, int i)
{
	if (options & 2)
		ft_putstr_fd("env : unsetenv ", 2);
	else
		ft_putstr_fd("env : setenv ", 2);
	ft_putstr_fd(tabb[i], 2);
	ft_putendl_fd(": Invalid argument", 2);
	return (USAGE);
}

t_err	invalid_opt_cd(char opt)
{
	ft_putstr_fd("\n21sh: -", 2);
	ft_putchar_fd(opt, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putstr_fd("cd: usage: cd [-L|-P] [dir]", 2);
	return (USAGE);
}
