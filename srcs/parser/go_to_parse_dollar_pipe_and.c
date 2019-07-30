/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_to_parse_dollar_pipe_and.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 11:28:03 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 13:17:11 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

t_bool		if_echap_and(char *str, int i, int c)
{
	if (i > 0 && str[i - 1] && str[i - 1] == '\\')
	{
		i--;
		while (i >= 0 && str[i] && str[i--] == '\\')
			c++;
		if (c == 0 || c % 2 == 0)
			return (FALSE);
	}
	if (c == 0)
		return (FALSE);
	return (TRUE);
}

static int	parse_redir_pipe_and(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '|' || str[i] == '&'))
	{
		if (str[i] == '|')
			return (unexpected_token("|"));
		return (unexpected_token("&"));
	}
	if ((parse_and_pipe(str + i, 0, '\0')) == USAGE)
		return (USAGE);
	return (SUCCESS);
}

int			parse_syntax_string(t_le *ledit)
{
	int		i;

	i = 0;
	if ((grab_dollar(ledit, ledit->buffer, &i, 0)) == USAGE)
		return (USAGE);
	if ((parse_redir_pipe_and(ledit->buffer, 0)) == USAGE)
		return (USAGE);
	return (SUCCESS);
}
