/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redir_left.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:57:51 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/29 17:34:04 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"
#include "error.h"

static int	fill_struct_redir_left(t_lst_tkn **lst, t_vred *vredir)
{
	t_lst_tkn	*tmp;

	tmp = (*lst);
	while (tmp->next)
		tmp = tmp->next;
	tmp->redir.i_out = -1;
	if (vredir->file == NULL)
	{
		if ((tmp->redir.out = ft_strdup("\n")) == NULL)
			return (MALLOC_FAIL);
	}
	else
	{
		if ((tmp->redir.out = ft_strdup(vredir->file)) == NULL)
			return (MALLOC_FAIL);
	}
	tmp->redir.i_in = vredir->a;
	if ((verif_int_std_one(tmp, vredir->a, ft_itoa(vredir->a))) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (vredir->file)
		free(vredir->file);
	if (vredir->arg_redir)
		free(vredir->arg_redir);
	return (SUCCESS);
}

int			s_redir(char **arg, char **save_buffer, char **buffer)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = *save_buffer;
	while (&(*tmp) != &(**buffer))
	{
		i++;
		tmp += 1;
	}
	if ((*arg = ft_strsub(*save_buffer, 0, i, 0)) == NULL)
		return (MALLOC_FAIL);
	return (SUCCESS);
}

int			handle_inredir(char **buffer, t_lst_tkn **lst)
{
	t_vred	vredir;
	int		ret;
	char	*tmp_buffer;

	tmp_buffer = (*buffer);
	ret = SUCCESS;
	initialize_var_redir(&vredir);
	vredir.a = 0;
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
	else if ((ret = add_token_to_list(lst, vredir.t_redi, vredir.arg_redir)) == MALLOC_FAIL)
		free_struct_vred(&vredir, lst);
	else if ((ret = fill_struct_redir_left(lst, &vredir)) == MALLOC_FAIL)
		free_struct_vred(&vredir, lst);
	return (ret);
}
