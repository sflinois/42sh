/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modif_keyboard_shell.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 10:29:35 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 11:57:15 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "ft_minishell.h"

static t_err	modif_keyboard_canon(struct termios term)
{
	if (((term.c_lflag & ICANON)) > 0)
	{
		term.c_lflag &= ~(ICANON);
		term.c_lflag &= ~(ECHO);
		term.c_lflag &= ~(ISIG);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
	}
	else
		return (SUCCESS);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
	{
		return (TERMCAPS);
	}
	return (SUCCESS);
}

t_err			initialize_keyboard(void)
{
	struct termios		term;
	char				*name_shell;
	int					success;

	if ((name_shell = getenv("TERM")) == NULL)
		name_shell = "xterm";
	success = tgetent(NULL, name_shell);
	if (success < 0)
	{
		ft_putendl("\nminishell: could not retrieve the termcaps date.");
		return (TERMCAPS);
	}
	if (success == 0)
	{
		ft_putendl("\nminishell: the given terminal type does not exist.");
		return (TERMCAPS);
	}
	if (tcgetattr(0, &term) == -1)
		return (TERMCAPS);
	if ((modif_keyboard_canon(term)) == TERMCAPS)
		return (TERMCAPS);
	return (SUCCESS);
}

int				reinitialize_keyboard(void)
{
	struct termios term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag |= (ICANON | ECHO | ISIG);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (-1);
	return (0);
}
