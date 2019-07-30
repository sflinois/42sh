/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 12:14:33 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:44:02 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

int		restore_std_fd()
{
	close(STDERR_FILENO);
	close(STDOUT_FILENO);
	if (dup(STDIN_FILENO) == -1)
		return (OPEN_FAIL); //check error return;
	if (dup(STDIN_FILENO) == -1)
		return (OPEN_FAIL);
	return 0;
}

void	putstr_with_prompt(int i_return, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		if (str[i] == '\n')
		{
			if (i_return == 0)
				ft_putstr("\x1B[32m");
			else
				ft_putstr("\x1B[31m");
			ft_putstr("         >\033[0m");
		}
		i++;
	}
}

void	print_my_prompt(t_le *ledit)
{
	ft_putstr("\x1B[32m");
	ft_putstr("[ 21sh ]");
	if (ledit->i_return == 0)
	{
		ft_putstr("\x1B[32m");
		ft_putstr("-> ");
		ft_putstr("\033[0m");
	}
	else
	{
		ft_putstr("\x1B[31m");
		ft_putstr("-> ");
		ft_putstr("\033[0m");
	}
	ledit->prompt = 1;
}

int		md_canon_print_prompt(t_le *ledit)
{
	if ((initialize_keyboard()) == TERMCAPS)
		return (TERMCAPS);
	if (restore_std_fd() == OPEN_FAIL)
		return (OPEN_FAIL);
	print_my_prompt(ledit);
	return (SUCCESS);
}
