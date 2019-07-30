/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar_posibility_expansion.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:18:28 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 13:21:21 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static int	basique_expansion(t_le *ledit, char *str, int *i)
{
	(*i)++;
	if (str[*i] && ft_strclen("-=+?", str[*i]) == -1)
		return (bad_use(str[*i]));
	(*i)++;
	if (str[*i] && str[*i] == '$' && str[(*i) + 1] && str[(*i) + 1] == '{')
	{
		(*i)++;
		if ((parse_brace(ledit, str, i)) == USAGE)
			return (USAGE);
	}
	while (str[*i] && if_alpha_or_digit(str[*i]) == 1)
		(*i)++;
	if (str[*i] == '\0' || (str[*i] && str[*i] != '}'))
		return (bad_use(str[*i]));
	(*i)++;
	return (SUCCESS);
}

static int	expansion_diez_percent(char *str, int *i, char c)
{
	(*i)++;
	if (str[*i] && str[*i] == '}')
		return (SUCCESS);
	if (str[*i] && str[*i] != c)
		return (bad_use(str[*i]));
	(*i)++;
	if (str[*i] == '\0' || (str[*i] && str[*i] != '}'))
		return (bad_use(str[*i]));
	(*i)++;
	return (SUCCESS);
}

int			check_possibility_expansion(t_le *ledit, char *str, int *i)
{
	if (str[*i] && str[*i] == ':')
	{
		if (basique_expansion(ledit, str, i) == USAGE)
			return (USAGE);
	}
	else if (str[*i] && (str[*i] == '%' || str[*i] == '#'))
	{
		if (expansion_diez_percent(str, i, str[*i]) == USAGE)
			return (USAGE);
	}
	else if (str[*i] && str[*i] == '$' && str[(*i) + 1] && str[(*i) + 1] == '{')
	{
		(*i)++;
		parse_brace(ledit, str, i);
	}
	else if (str[*i] == '\0' || (str[*i] && str[*i] != '}'))
		return (bad_use(str[*i]));
	return (SUCCESS);
}
