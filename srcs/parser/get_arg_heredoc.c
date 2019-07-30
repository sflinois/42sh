/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 11:57:07 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 13:14:54 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static int	get_eof(char *str, int i, char **eof)
{
	int		s;

	s = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && if_alpha_or_digit(str[i]) == 1)
	{
		i++;
		s++;
	}
	if (s > 0)
	{
		if ((*eof = ft_strsub(str, i - s, s, 0)) == NULL)
			return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

static int	recup_eof_and_arg_heredoc(t_le *ledit, char *str, int i)
{
	char	*eof;
	char	*strim;

	strim = NULL;
	eof = NULL;
	if ((get_eof(str, i, &eof)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if ((get_end_heredoc(ledit, str, eof, &strim)) == MALLOC_FAIL)
	{
		free(eof);
		return (MALLOC_FAIL);
	}
	if ((create_list_heredoc(strim, ledit)) == MALLOC_FAIL)
	{
		free(eof);
		if (strim != NULL)
			free(strim);
		return (MALLOC_FAIL);
	}
	free(eof);
	return (SUCCESS);
}

int			get_arg_heredoc(char *str, t_le *ledit, int i)
{
	int		nb_heredoc;
	int		x;

	x = 0;
	nb_heredoc = nb_heredoc_parse(&ledit->list_heredoc);
	while (str[i])
	{
		if (str[i] == '<' \
		&& str[i + 1] && str[i + 1] == '<' \
		&& if_echap_and(str, i, 0) == FALSE &&
		nb_heredoc <= x++)
		{
			recup_eof_and_arg_heredoc(ledit, str, (i + 2));
		}
		i++;
	}
	return (SUCCESS);
}
