/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_other.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 16:31:30 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:05:57 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

t_err	print_fail_open(char *file)
{
	ft_putstr_fd("\x1B[31m$My_21sh > \033[0m", 2);
	ft_putstr_fd("21sh: open error: ", 2);
	ft_putendl_fd(file, 2);
	free(file);
	return (OPEN_FAIL);
}

t_err	unexpected_token(char *str)
{
	ft_putstr_fd("\n21sh: syntax error near unexpected token `", 2);
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\'', 2);
	return (USAGE);
}

int		ft_print_error_heredoc(char c)
{
	ft_putstr_fd("\n21sh: ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(": invalid heredoc (alpha-numeric)", 2);
	return (USAGE);
}

t_err	print_error_illegal_options(void)
{
	ft_putendl_fd("21sh: illegal options", 2);
	return (USAGE);
}

t_err	error_command_not_found(char *str)
{
	ft_putstr_fd("21sh: command not found : ", 2);
	ft_putendl_fd(str, 2);
	return (USAGE);
}
