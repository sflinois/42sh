/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe_and.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 14:37:04 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/05 15:02:08 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static int		check_triple_charac(char *str, char c)
{
	int		i;
	int		x;

	x = 0;
	i = 0;
	while (str[i] && str[i] == c)
	{
		i++;
		x++;
		if (x == 3)
		{
			if (c == '&')
				return (unexpected_token("&"));
			else
				return (unexpected_token("|"));
		}
	}
	return (SUCCESS);
}

static t_bool	check_next_char(char *str, int i)
{
	if (str[i] && str[i] == '&')
		return (TRUE);
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && ft_strclen("&|;", str[i]) > -1)
		return (FALSE);
	return (TRUE);
}

static int		check_charac_with_and(char *str, int i, int b)
{
	if (check_next_char(str, i + 1) == FALSE)
		b = -1;
	if (str[i + 1] == '&' && (str[i - 1] == '<' || str[i - 1] == '>'))
		b = -1;
	if (b == -1)
		return (unexpected_token("&"));
	return (SUCCESS);
}

static int		check_charac_with_pipe(char *str, int i)
{
	while (str[i] == '|')
		i++;
	while (str[i] == ' ')
		i++;
	if (str[i] && ft_strclen("&|;", str[i]) > -1)
		return (unexpected_token("|"));
	return (0);
}

int				parse_and_pipe(char *str, int i, char f)
{
	while (str[i])
	{
		if (str[i] == (f = find_char_in_str(str[i], "\"'")))
			if ((go_next_same_char(str, &i, f)) == -1)
				return (0);
		if (str[i] == '&' && if_echap_and(str, i, 0) == FALSE \
		&& ((check_charac_with_and(str, i, 0)) == USAGE \
		|| (check_triple_charac(str + i, '&')) == USAGE))
			return (USAGE);
		else if (str[i] == '|' && (if_echap_and(str, i, 0)) == FALSE \
		&& (check_charac_with_pipe(str, i) == USAGE \
		|| check_triple_charac(str + i, '|') == USAGE))
			return (USAGE);
		else if ((str[i] == '<' || str[i] == '>') \
		&& (if_echap_and(str, i, 0)) == FALSE \
		&& check_charac_after_redir(str, i + 1, '\0') == USAGE)
			return (USAGE);
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<' \
		&& if_echap_and(str, i, 0) == FALSE \
		&& parse_string_after_heredoc(str, i + 2) == USAGE)
			return (USAGE);
		i++;
	}
	return (SUCCESS);
}
