/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redir_right.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:43:40 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/29 17:09:56 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "error.h"

void		initialize_var_redir(t_vred *vredir)
{
	vredir->t_redi = 0;
	vredir->a = 1;
	vredir->chain = 0;
	vredir->file = NULL;
	vredir->arg_redir = NULL;
}

void		free_struct_vred(t_vred *vredir, t_lst_tkn **lst)
{
	if (vredir->file != NULL)
		free(vredir->file);
	if ((*lst) != NULL)
		free_list_tkn(lst);
	if (vredir->arg_redir != NULL)
		free(vredir->arg_redir);
}

static int	fill_struct_redir_right(t_lst_tkn **lst, t_vred *vredir)
{
	t_lst_tkn	*tmp;

	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->redir.i_out = vredir->a;
	if ((verif_int_std_in(tmp, vredir->a, NULL)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (vredir->file && (vredir->a = protect_atoi(vredir->file, 0)) >= 0)
		tmp->redir.i_in = -1;
	else
		tmp->redir.i_in = -1;
	if (vredir->file != NULL)
	{
		if ((verif_int_std_one(tmp, vredir->a, vredir->file)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	else
	{
		if ((tmp->redir.in = ft_strdup("\n")) == NULL)
			return (MALLOC_FAIL);
	}
	if (vredir->arg_redir)
		free(vredir->arg_redir);
	return (SUCCESS);
}

int			handle_outredir(char **buffer, t_lst_tkn **lst)
{
	t_vred	vredir;
	int		ret;
	char	*tmp_buffer;

	tmp_buffer = (*buffer);
	initialize_var_redir(&vredir);
	ret = SUCCESS;
	if (**buffer != '\0' && **buffer >= 48 && **buffer <= 57)
		get_number_fd(buffer, &vredir.a);
	define_token_redir(buffer, &vredir.t_redi, 0);
	if (**buffer)
	{
		if ((get_file_redir(buffer, 0, &vredir.file)) == MALLOC_FAIL)
			return (MALLOC_FAIL);
	}
	if ((ret = s_redir(&vredir.arg_redir, &tmp_buffer, buffer)) == MALLOC_FAIL)
		free_struct_vred(&vredir, lst);
	else if ((ret = add_token_to_list(lst, vredir.t_redi, vredir.arg_redir)) \
		== MALLOC_FAIL)
		free_struct_vred(&vredir, lst);
	else if ((fill_struct_redir_right(lst, &vredir)) == MALLOC_FAIL)
		free_struct_vred(&vredir, lst);
	return (ret);
}
