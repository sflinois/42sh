/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 17:17:23 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 13:24:39 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

int			parse_string_after_heredoc(char *str, int i)
{
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0' || (str[i] && str[i] == '\n'))
	{
		return (unexpected_token("newline"));
	}
	if (if_alpha_or_digit(str[i]) == 1)
		return (0);
	return (ft_print_error_heredoc(str[i]));
}

static int	check_redir_rightand(char *str, int i)
{
	int		j;
	char	str_right[520];
	int		alpha;

	alpha = 0;
	j = 0;
	ft_bzero(&str_right, sizeof(char) * 520);
	while (str[i] && ft_strclen("|&<> ;", str[i]) == -1)
		str_right[j++] = str[i++];
	j = 0;
	while (str_right[j])
	{
		if (ft_isalpha(str_right[j]) == 1)
			alpha = 1;
		j++;
	}
	if (str_right[j - 1] && str_right[j - 1] == '-')
	{
		if (alpha == 1)
			return (ambiguous_redirect());
	}
	return (SUCCESS);
}

static int	check_which_redir_is(char *str_redir, char *str, int i)
{
	if ((ft_strcmp(str_redir, "<<") == 0 || ft_strcmp(str_redir, ">>") == 0) \
	&& str[i] && str[i] == '&')
		return (unexpected_token("&"));
	else if (ft_strcmp(str_redir, "<") == 0 && str[i] && str[i] == '&')
	{
		i++;
		while (str[i] && ft_isdigit(str[i]) == 1)
			i++;
		if (str[i] && ft_strclen("&|;<>-", str[i]) == -1)
			return (ambiguous_redirect());
		if (str[i] && str[i] == '-')
		{
			if (str[i + 1] && ft_strclen("&|;<> ", str[i + 1]) == -1 \
			&& ft_isalnum(str[i + 1]) == -1)
				return (ambiguous_redirect());
		}
	}
	else if (ft_strcmp(">", str_redir) == 0 && str[i] && str[i] == '&')
	{
		if ((check_redir_rightand(str, i + 1)) == USAGE)
			return (USAGE);
	}
	return (0);
}

static int	check_valide_redir(char *str, int i)
{
	int		ret;
	int		j;
	char	str_redir[520];

	ft_bzero(&str_redir, sizeof(char) * 520);
	j = 0;
	ret = 0;
	if (str[i] == '>' && str[i + 1] && str[i + 1] == '<')
		return (unexpected_token("<"));
	else if (str[i] == '<' && str[i + 1] && str[i + 1] == '>')
		return (unexpected_token(">"));
	else
	{
		while (str[i] && (str[i] == '<' || str[i] == '>'))
			str_redir[j++] = str[i++];
		if (check_which_redir_is(str_redir, str, i) == USAGE)
			return (USAGE);
	}
	return (ret);
}

int			check_charac_after_redir(char *str, int i, char c)
{
	if (check_valide_redir(str, i - 1) == USAGE)
		return (USAGE);
	if (ft_strclen("<>", str[i]) != -1)
		i++;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '|')
		return (unexpected_token("|"));
	else if (if_alpha_or_digit(str[i]) == -1 \
			&& ft_strclen("&'\"/", str[i]) == -1)
		return (unexpected_token("bad file descriptor"));
	else if ((str[i] == '&' && str[i + 1] == '\0') \
	|| (str[i] == '&' && str[i + 1] && str[i + 1] != '-' \
		&& if_alpha_or_digit(str[i + 1]) == -1))
		return (unexpected_token("bad file descriptor"));
	else if (str[i] && ft_strclen("<>", str[i]) != -1)
		return (unexpected_token("<"));
	else if (str[i] == c)
		return (unexpected_token("newline"));
	return (SUCCESS);
}
