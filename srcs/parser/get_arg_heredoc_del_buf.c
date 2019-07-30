/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_heredoc_del_buf.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 13:11:32 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 13:25:33 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static void	del_char_heredoc(t_le *ledit, char *str, int j, int i)
{
	while (j > 0)
	{
		if (str[i] == '\n')
		{
			j--;
			if (ledit->c_del == 0)
			{
				ledit->index_buffer++;
				ledit->c_del = 1;
			}
			while (i > 0 && str[i] && str[i] == '\n')
			{
				str[i] = ' ';
				i--;
			}
		}
		else
		{
			str[i] = ' ';
			i--;
		}
	}
}

static void	delete_arg_heredoc_in_str(t_le *ledit, char *str, int x)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	if (ledit->list_heredoc)
		j -= ledit->nb_inhib_miss;
	while (str[i] && j < x)
	{
		if (str[i] == '\n')
			j++;
		i++;
		while (str[i] && str[i] == '\n')
			i++;
		while (str[i] && str[i] != '\n')
			i++;
	}
	if (str[i] && str[i] == '\n')
		i--;
	del_char_heredoc(ledit, str, j, i);
}

static int	get_arg_in_tab(char **tabb, int i, char **strim)
{
	int		j;

	j = 1;
	while (j < i)
	{
		if (j == 1)
		{
			if ((*strim = ft_strdup(tabb[j])) == NULL)
				return (MALLOC_FAIL);
		}
		else if (j > 1)
		{
			if ((*strim = ft_strjoinfree(*strim, tabb[j], 1)) == NULL)
				return (MALLOC_FAIL);
		}
		j++;
		if ((*strim = ft_strjoinfree(*strim, "\n", 1)) == NULL)
			return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

static int	free_return_fail(char **tabb)
{
	ft_free_tab(tabb);
	return (MALLOC_FAIL);
}

int			get_end_heredoc(t_le *ledit, char *str, char *eof, char **strim)
{
	int		i;
	char	**tabb;

	if ((tabb = ft_strsplit(str, '\n')) == NULL)
		return (MALLOC_FAIL);
	i = 0;
	while (tabb[i])
	{
		if ((*strim = ft_strtrim(tabb[i], 0)) == NULL)
			return (free_return_fail(tabb));
		if (ft_strcmp(tabb[i], eof) == 0)
		{
			free(*strim);
			*strim = NULL;
			if ((get_arg_in_tab(tabb, i, strim)) == MALLOC_FAIL)
				return (free_return_fail(tabb));
			delete_arg_heredoc_in_str(ledit, str, i);
			ft_free_tab(tabb);
			return (SUCCESS);
		}
		else
			free(*strim);
		i++;
	}
	return (SUCCESS);
}
