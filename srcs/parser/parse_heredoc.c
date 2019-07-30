/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 14:17:49 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 13:00:49 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static char		*save_first_string(char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while (str[i] && if_alpha_or_digit(str[i]) == 1)
		i++;
	if (i > 0)
	{
		if ((tmp = ft_strsub(str, 0, i, 0)) == NULL)
			return (NULL);
	}
	str += i;
	return (tmp);
}

static t_bool	check_end_of_file(char *str, char *eof)
{
	char	**tabb;
	int		i;

	i = 0;
	if ((tabb = ft_strsplit(str, '\n')) == NULL)
		return (MALLOC_FAIL);
	while (tabb[i])
	{
		if (ft_strcmp(tabb[i], eof) == 0)
		{
			free(eof);
			ft_free_tab(tabb);
			return (TRUE);
		}
		i++;
	}
	ft_free_tab(tabb);
	free(eof);
	return (FALSE);
}

int				nb_heredoc_parse(t_list_eof **lst)
{
	t_list_eof	*tmp;
	int			i;

	i = 0;
	tmp = (*lst);
	if (!tmp)
		return (0);
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

static t_bool	check_about_heredoc(char *str, int i)
{
	char	*tmp;

	tmp = NULL;
	while (str[i] && str[i] == ' ')
		i++;
	if ((tmp = save_first_string(str + i)) == NULL)
		return (MALLOC_FAIL);
	if (check_end_of_file(str, tmp) == FALSE)
		return (FALSE);
	return (TRUE);
}

int				verif_heredoc(t_le *ledit, char *str, int i)
{
	int		nb_heredoc;
	int		x;
	int		ret;

	ret = 0;
	x = 0;
	nb_heredoc = nb_heredoc_parse(&ledit->list_heredoc);
	while (str[i])
	{
		if (check_quote_close(str, &i) == FALSE)
			return (0);
		if (str[i] == '<' && str[i + 1] && str[i + 1] == '<' && \
				if_echap_and(str, i, 0) == FALSE && nb_heredoc <= x++)
		{
			if ((ret = check_about_heredoc(str, i + 2)) == FALSE)
				return (FALSE);
			if (ret == MALLOC_FAIL)
				return (MALLOC_FAIL);
		}
		i++;
	}
	return (TRUE);
}
