/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_substitution.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 15:57:34 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/14 16:51:20 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

int		bracket_error(void)
{
	ft_putstr_fd("\n21sh: $(simple command)", 2);
	return (USAGE);
}

int		bad_charac(char c)
{
	ft_putstr_fd("\n21sh: ", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd(": error. need alpha_digit character", 2);
	return (USAGE);
}

int		bad_use(char c)
{
	ft_putstr_fd("\n21sh: ", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd(": ${param[:- := :+ :?][word(alpha-numeric)]}", 2);
	ft_putstr_fd("       : ${param[%.%%.#.##]}", 2);
	return (USAGE);
}

void	param_null_not_set(char *str)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(": parameter null or not set", 2);
}

void	param_null_with_arg(char *param, char *value)
{
	ft_putstr_fd("21sh: ", 2);
	ft_putstr_fd(param, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(value, 2);
}
