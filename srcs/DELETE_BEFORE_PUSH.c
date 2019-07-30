/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DELETE_BEFORE_PUSH.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 15:34:06 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/29 17:07:43 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_print_histo(t_listhisto **list)
{
	t_listhisto	*tmp;

	tmp = (*list);
	while (tmp)
	{
		ft_putendl(tmp->line);
		tmp = tmp->prev;
	}
}

void		ft_print_list_tkn(t_lst_tkn **lst)
{
	t_lst_tkn	*tmp;

	tmp = (*lst);
	// func a supprimer
	if (tmp == NULL)
	{
		ft_putendl("liste token non existante\n");
		return ;
	}
	while (tmp)
	{
		 ft_printf("ordre -> %s et -> numero d'ordre %d\n",
				 tmp->order, tmp->nb_order);
		if ((tmp->nb_order >= 3 && tmp->nb_order <= 7) || tmp->nb_order == 99)
		{
			ft_printf("out -> %d && in -> %d\n", tmp->redir.i_out, tmp->redir.i_in);
			if (tmp->redir.out != NULL)
				ft_printf("redir out = %s\n", tmp->redir.out);
			if (tmp->redir.arg_heredoc != NULL)
				ft_printf("arg du redir = |%s|\n", tmp->redir.arg_heredoc);
			if (tmp->redir.in != NULL)
				ft_printf("redir in = %s\n", tmp->redir.in);
		}
		tmp = tmp->next;
	}
	ft_putendl("\nfin d'affichage de liste\n");
}