/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redir_global.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 14:07:27 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 15:32:39 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "error.h"

int			verif_int_std_in(t_lst_tkn *tmp, int a, char *file)
{
	(void)file;
	if (a == 0)
	{
		if ((tmp->redir.out = ft_strdup("std_in")) == NULL)
			return (MALLOC_FAIL);
	}
	else if (a == 1)
	{
		if ((tmp->redir.out = ft_strdup("std_out")) == NULL)
			return (MALLOC_FAIL);
	}
	else if (a == 2)
	{
		if ((tmp->redir.out = ft_strdup("std_err")) == NULL)
			return (MALLOC_FAIL);
	}
	else
	{
		if ((tmp->redir.out = ft_itoa(a)) == NULL)
			return (MALLOC_FAIL);
	}
	return (SUCCESS);
}

int			verif_int_std_one(t_lst_tkn *tmp, int a, char *file)
{
	if (a == 0)
	{
		if ((tmp->redir.in = ft_strdup("std_in")) == NULL)
			return (MALLOC_FAIL);
	}
	else
	{
		if ((tmp->redir.in = ft_strdup(file)) == NULL)
			return (MALLOC_FAIL);
	}
	free(file);
	return (SUCCESS);
}

void		define_token_redir(char **buffer, int *t_redi, int i)
{
	while ((*buffer)[i] && ((*buffer)[i] == '>' || (*buffer)[i] == '<'))
		i++;
	if (i == 1)
	{
		if (*buffer && **buffer && **buffer == '<')
			*t_redi = T_REDI_L;
		else if (*buffer && **buffer && **buffer == '>')
			*t_redi = T_REDI_R;
	}
	if (i == 2)
	{
		if (*buffer && **buffer && **buffer == '<')
			*t_redi = T_REDI_LL;
		else if (*buffer && **buffer && **buffer == '>')
			*t_redi = T_REDI_RR;
	}
	*buffer = *buffer + i;
}

void		get_number_fd(char **buffer, int *a)
{
	int		i;
	char	nb_fd[520];

	ft_bzero(&nb_fd, sizeof(char) * 520);
	i = 0;
	while ((*buffer)[i] && (*buffer)[i] >= 48 && (*buffer)[i] <= 57)
	{
		nb_fd[i] = (*buffer)[i];
		i++;
	}
	*buffer = *buffer + i;
	(*a) = ft_atoi(nb_fd);
}

int			get_file_redir(char **str, int i, char **file)
{
	(*file) = NULL;
	while (**str && **str == ' ')
		(*str)++;
	if ((*str)[i] && (*str)[i] == '&' && (*str)[i + 1] && (*str)[i + 1] == '-')
	{
		*str += 2;
		if (((*file) = ft_strdup("&-")) == NULL)
			return (MALLOC_FAIL);
	}
	else if ((*str)[i] && ((*str)[i] == '\'' || (*str)[i] == '\"'))
	{
		if ((handle_dquote_redir(str, file, (*str)[i])) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	else if ((*str)[i])
	{
		if ((*str)[i] && (*str)[i] == '&')
			(*str) += ++i;
		if ((recup_others(str, file)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
		if (i == 1 && (((*file) = ft_strjoinfree("&", *file, 2)) == NULL))
			return (MALLOC_FAIL);
	}
	return (SUCCESS);
}
