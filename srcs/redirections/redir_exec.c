/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 11:49:06 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/15 12:09:35 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir_exec.h"

void	remove_redir_from_lst(t_lst_tkn **tkn_lst)
{
	t_lst_tkn *tmp_tkn;
	t_lst_tkn *tmp_lst;

	while (tkn_lst && *tkn_lst && (*tkn_lst)->nb_order >= T_REDI_R
		&& (*tkn_lst)->nb_order <= T_REDI_LR)
	{
		tmp_tkn = *tkn_lst;
		*tkn_lst = (*tkn_lst)->next;
		free_tkn(tmp_tkn);
	}
	tmp_lst = *tkn_lst;
	while (tmp_lst)
	{
		while (tmp_lst->next && tmp_lst->next->nb_order >= T_REDI_R
			&& tmp_lst->next->nb_order <= T_REDI_LR)
		{
			tmp_tkn = tmp_lst->next;
			tmp_lst->next = tmp_lst->next->next;
			free_tkn(tmp_tkn);
		}
		tmp_lst = tmp_lst->next;
	}
}

int		exec_output_redir(t_lst_tkn *lst, t_lst_fd **fd_lst, int *standart_fd)
{
	int		ret;

	ret = 0;
	if (lst->nb_order == T_REDI_R)
	{
		if (lst->redir.in[0] == '&')
		{
			if (ft_strcmp(lst->redir.out, "&-") == 0)
				ret = close_fd(lst->redir.i_in,
						lst->redir.i_out, fd_lst, standart_fd);
			else
				ret = redir_fd(lst->redir.i_in,
						lst->redir.i_out, fd_lst, standart_fd);
		}
		else
			ret = redir_output(lst->redir.i_out,
					lst->redir.in, fd_lst, standart_fd);
	}
	else if (lst->nb_order == T_REDI_RR)
		ret = redir_append(STDOUT_FILENO, lst->redir.in, fd_lst, standart_fd);
	return (ret);
}

int		exec_input_redir(t_lst_tkn *lst, t_lst_fd **fd_lst, int *standart_fd)
{
	int		ret;

	ret = 0;
	if (lst->nb_order == T_REDI_L)
	{
		if (lst->redir.out[0] == '&')
		{
			if (ft_strcmp(lst->redir.out, "&-") == 0)
				ret = close_fd(lst->redir.i_out,
						lst->redir.i_in, fd_lst, standart_fd);
			else
				ret = redir_fd(lst->redir.i_out,
						lst->redir.i_in, fd_lst, standart_fd);
		}
		else
			ret = redir_input(lst->redir.out,
					STDIN_FILENO, fd_lst, standart_fd);
	}
	else if (lst->nb_order == T_REDI_LL)
		ret = redir_heredoc(lst->redir.arg_heredoc, fd_lst, standart_fd);
	return (ret);
}

int		start_redir(t_lst_tkn **tkn_lst, t_lst_fd **fd_lst, int *standart_fd)
{
	t_lst_tkn	*lst;
	int			ret;

	lst = *tkn_lst;
	ret = 0;
	while (lst && ret >= 0)
	{
		if (lst->nb_order == T_REDI_R && lst->redir.in[0] == '&')
			correct_redir_r(&(lst->redir));
		if (lst->nb_order == T_REDI_L && lst->redir.out[0] == '&')
			correct_redir_l(&(lst->redir));
		if (lst->nb_order == T_REDI_R || lst->nb_order == T_REDI_RR)
			ret = exec_output_redir(lst, fd_lst, standart_fd);
		else if (lst->nb_order == T_REDI_L || lst->nb_order == T_REDI_LL)
			ret = exec_input_redir(lst, fd_lst, standart_fd);
		lst = lst->next;
	}
	remove_redir_from_lst(tkn_lst);
	return (ret);
}
