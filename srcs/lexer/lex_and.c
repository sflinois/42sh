/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_and.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 13:44:17 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/14 11:05:25 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "error.h"

int		handle_pipe(char **buffer, t_lst_tkn **lst)
{
	int		i;

	i = 1;
	if ((*buffer)[i] && (*buffer)[i] == '|')
	{
		if ((add_token_to_list(lst, T_OR, "||")) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		*buffer += 2;
	}
	else if (((*buffer)[i] == '\0') || ((*buffer)[i] && (*buffer)[i] != '|'))
	{
		if ((add_token_to_list(lst, T_PIPE, "|")) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		*buffer += 1;
	}
	return (0);
}

int		handle_and(char **buffer, t_lst_tkn **lst)
{
	int		i;

	i = 1;
	(void)lst;
	if ((*buffer)[i] && (*buffer)[i] == '&')
	{
		if ((add_token_to_list(lst, T_AND, "&&")) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		*buffer = *buffer + 2;
	}
	else
	{
		if ((add_token_to_list(lst, T_JOB, "&")) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		*buffer += 1;
	}
	return (0);
}

int		handle_semico(char **buffer, t_lst_tkn **lst)
{
	if (**buffer == ';')
	{
		if ((add_token_to_list(lst, T_SEMICO, ";")) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		*buffer = *buffer + 1;
	}
	return (SUCCESS);
}
