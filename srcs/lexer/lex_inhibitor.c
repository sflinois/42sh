/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_inhibitor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 14:50:45 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/29 17:58:59 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "ft_minishell.h"
#include "error.h"

int		size_of_arg(char **buffer, int *x, char c)
{
	echap_charac(*buffer, *x);
	if (*buffer && ft_strclen("\"\'", (*buffer)[*x]) > -1)
	{
		echap_charac(*buffer, *x);
	}
	else
	{
		go_next_same_char(*buffer, x, c);
		echap_charac(*buffer, *x);
	}
	while ((*buffer)[*x] && ft_strclen("|&<># ;", (*buffer)[*x]) == -1)
	{
		if (((*buffer)[*x] == '"' || (*buffer)[*x] == '\'') \
				&& if_echap_and(*buffer, *x, 0) == FALSE)
			size_of_arg(buffer, x, (*buffer)[*x]);
		(*x)++;
	}
	(*x)--;
	return (0);
}

int		handle_squote(char **buffer, t_lst_tkn **lst)
{
	int		x;
	char	*tmp;

	x = 0;
	size_of_arg(buffer, &x, '\'');
	if ((tmp = ft_strsub(*buffer, 0, x + 1, 0)) == NULL)
		return (MALLOC_FAIL);
	x = ft_strlen(tmp);
	*buffer = *buffer + x;
	if ((add_token_to_list(lst, T_SQUOTE, tmp)) == MALLOC_FAIL)
	{
		free(tmp);
		return (MALLOC_FAIL);
	}
	free(tmp);
	return (0);
}

int		handle_dquote(char **buffer, t_lst_tkn **lst)
{
	int		x;
	char	*tmp;

	x = 0;
	size_of_arg(buffer, &x, '"');
	if ((tmp = ft_strsub(*buffer, 0, x + 1, 0)) == NULL)
		return (MALLOC_FAIL);
	x = 0;
	while (tmp[x])
	{
		if (tmp[x] == '\\')
			echap_charac(tmp, x);
		else
			x++;
	}
	*buffer = *buffer + x;
	if ((add_token_to_list(lst, T_DQUOTE, tmp)) == MALLOC_FAIL)
	{
		free(tmp);
		return (MALLOC_FAIL);
	}
	free(tmp);
	return (0);
}

int		handle_dquote_redir(char **buffer, char **file, char c)
{
	int		x;

	x = 0;
	size_of_arg(buffer, &x, c);
	if (((*file) = ft_strsub(*buffer, 0, x + 1, 0)) == NULL)
		return (MALLOC_FAIL);
	x = ft_strlen(*file);
	*buffer = *buffer + x;
	if (c == '"')
	{
		x = 0;
		while ((*file)[x])
		{
			if ((*file)[x] == '\\')
				echap_charac((*file), x);
			else
				x++;
		}
	}
	return (SUCCESS);
}
