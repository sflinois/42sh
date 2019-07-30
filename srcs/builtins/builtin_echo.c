/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 18:07:54 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/14 16:43:54 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

int		recup_opt(char **tabb, int *opt, int *j)
{
	int		i;

	i = 0;
	(*opt) = 0;
	while (tabb[*j])
	{
		if (tabb[*j][i] && tabb[*j][i] == '-')
		{
			i++;
			if (tabb[*j][i] && ft_strcmp(tabb[*j] + i, "n") == 0)
			{
				*opt = 1;
			}
			else
				return (0);
		}
		else
			return (0);
		(*j)++;
	}
	return (0);
}

t_err	builtin_echo(t_mini *minishell)
{
	int		i;
	int		j;
	int		opt;

	j = 1;
	i = 0;
	recup_opt(minishell->tab_argv_split, &opt, &j);
	if (minishell->tab_argv_split[1] != NULL)
	{
		while (minishell->tab_argv_split[j])
		{
			while (minishell->tab_argv_split[j][i] != '\0')
			{
				ft_putchar(minishell->tab_argv_split[j][i]);
				i++;
			}
			if (minishell->tab_argv_split[j + 1] != NULL)
				ft_putchar(' ');
			j++;
			i = 0;
		}
		if (opt == 0)
			ft_putchar('\n');
	}
	return (SUCCESS);
}
