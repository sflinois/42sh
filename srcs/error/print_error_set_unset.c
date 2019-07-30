/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_set_unset.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 11:14:14 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:06:06 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

t_err	check_nb_arg(int nb_arg)
{
	if (nb_arg < 2)
	{
		ft_putstr_fd("Too few arguments : ", 2);
		ft_putendl_fd("setenv [name=[value]]", 2);
		return (USAGE);
	}
	else if (nb_arg > 2)
	{
		ft_putstr_fd("Too many arguments : ", 2);
		ft_putendl_fd("setenv [name=[value]]", 2);
		return (USAGE);
	}
	return (SUCCESS);
}

t_err	check_nb_arg_unset(int nb_arg)
{
	if (nb_arg < 2)
	{
		ft_putstr_fd("Too few arguments : ", 2);
		ft_putendl_fd("unsetenv [name]", 2);
		return (USAGE);
	}
	if (nb_arg > 2)
	{
		ft_putstr_fd("Too many arguments : ", 2);
		ft_putendl_fd("unsetenv [name]", 2);
		return (USAGE);
	}
	return (SUCCESS);
}

t_err	error_unset(void)
{
	ft_putendl_fd("unset : not enough arguments", 2);
	return (USAGE);
}

t_err	ft_print_error_set(char *str, int i)
{
	if (i == 0)
	{
		ft_putstr_fd("21sh: set `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
	else if (i == 1)
	{
		ft_putstr_fd("21sh: unset `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
	else if (i == 2)
	{
		ft_putstr_fd("21sh: export `", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd("': not a valid identifier", 2);
	}
	return (USAGE);
}
