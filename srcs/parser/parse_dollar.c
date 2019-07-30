/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/17 14:27:13 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 13:20:04 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static int	parse_diez(char *str, int *i)
{
	(*i)++;
	while (str[*i] && if_alpha_or_digit(str[*i]) == 1)
		(*i)++;
	if (str[*i] == '\0' || (str[*i] && str[*i] != '}'))
		return (bad_use(str[*i]));
	(*i)++;
	return (SUCCESS);
}

static int	parse_last_return(char *str, int *i)
{
	(*i)++;
	if (str[*i] && str[*i] != '}')
	{
		ft_putstr_fd("\n21sh : no character: ${?}", 2);
		return (USAGE);
	}
	return (0);
}

int			parse_brace(t_le *ledit, char *str, int *i)
{
	(*i)++;
	if (str[*i] && str[*i] == '!')
	{
		if ((recup_history(ledit, *i)) == USAGE)
			return (USAGE);
	}
	if (str[*i] && str[*i] == '#')
		return (parse_diez(str, i));
	else if (str[*i] == '?')
		return (parse_last_return(str, i));
	else if (str[*i] && if_alpha_or_digit(str[(*i)++]) == -1)
		return (bad_use(str[*i]));
	while (str[*i] && if_alpha_or_digit(str[*i]) == 1)
		(*i)++;
	if ((check_possibility_expansion(ledit, str, i)) == USAGE)
		return (USAGE);
	return (SUCCESS);
}

int			grab_dollar(t_le *ledit, char *str, int *i, int ret)
{
	while (str[*i])
	{
		if (str[*i] == '\'' && if_echap_and(str, *i, 0) == FALSE)
			go_next_same_char(str, i, '\'');
		if (str[*i] == '$' && (if_echap_and(str, *i, 0)) == FALSE)
		{
			(*i)++;
			if (str[*i] && str[*i] == '{')
				ret = parse_brace(ledit, str, i);
			else
				ret = bad_use(str[*i]);
			if (ret < 0)
				return (ret);
		}
		else if (str[*i] == '!' && if_echap_and(ledit->buffer, *i, 0) == FALSE)
		{
			if ((recup_history(ledit, *i)) == USAGE)
				return (USAGE);
		}
		else
			(*i)++;
	}
	return (SUCCESS);
}
