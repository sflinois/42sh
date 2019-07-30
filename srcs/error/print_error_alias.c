/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_alias.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 17:30:01 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/31 18:14:07 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

int			error_alias_use_alias_unalias(char *func, char *error)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(func, 2);
	ft_putstr_fd("can't alias/unalias arg :", 2);
	ft_putendl_fd(error, 2);
	return (USAGE);
}

int			error_options_alias(char *func, char error, char opt)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(func, 2);
	ft_putstr_fd(": -", 2);
	ft_putchar_fd(error, 2);
	ft_putendl_fd(": invalid option", 2);
	ft_putstr_fd("alias: usage: alias [-", 2);
	ft_putchar_fd(opt, 2);
	ft_putendl_fd("] [name[=value] ... ]", 2);
	return (USAGE);
}

int			error_not_found_alias(char *func, char *error)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(func, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd(": not found", 2);
	return (USAGE);
}