/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_others.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 17:46:18 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/14 11:08:07 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "error.h"

static void	size_arg_other(char *str, int *i)
{
	char	f;

	f = '\0';
	while (str[*i] && ft_strclen("|&<> ;", str[*i]) == -1)
	{
		if (str[*i] == '\\')
		{
			echap_charac(str, *i);
			if (str[*i])
				(*i)++;
		}
		if (str[*i] && str[*i] == (f = find_char_in_str(str[*i], "\"'")))
		{
			echap_charac(str, *i);
			go_next_same_char(str, i, f);
			echap_charac(str, *i);
		}
		else if (str[*i])
			(*i)++;
	}
}

int			recup_others(char **buffer, char **file)
{
	int		i;
	char	*str;

	str = *buffer;
	i = 0;
	size_arg_other(str, &i);
	if (i > 0)
	{
		if (((*file) = ft_strsub(*buffer, 0, i, 0)) == NULL)
			return (MALLOC_FAIL);
		*buffer = *buffer + i;
	}
	return (0);
}

int			check_if_redir(char **buffer, t_lst_tkn **lst)
{
	int		i;
	char	c;

	i = 0;
	(void)lst;
	while ((*buffer)[i] && (*buffer)[i] >= 48 && (*buffer)[i] <= 57)
		i++;
	c = (*buffer)[i];
	if (i > 0 && c != '\0' && (c == '>' || c == '<'))
	{
		if (c == '>')
		{
			if ((handle_outredir(buffer, lst)) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		}
		else if (c == '<')
		{
			if ((handle_inredir(buffer, lst)) == MALLOC_FAIL)
				return (MALLOC_FAIL);
		}
	}
	else
		return (-1);
	return (0);
}

int			handle_others(char **buffer, t_lst_tkn **lst)
{
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = NULL;
	if ((ret = check_if_redir(buffer, lst)) == 0)
		return (0);
	else if (ret == MALLOC_FAIL)
		return (MALLOC_FAIL);
	else
	{
		if ((recup_others(buffer, &tmp)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		if ((add_token_to_list(lst, T_COMMAND, tmp)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		free(tmp);
	}
	return (0);
}
