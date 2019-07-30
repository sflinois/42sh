/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/10 13:36:03 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/10 13:37:59 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

void	ft_print_list(t_listenv **list)
{
	t_listenv *tmp;

	tmp = (*list);
	if (!(tmp))
		return ;
	while (tmp)
	{
		ft_putendl(tmp->str_env);
		tmp = tmp->next;
	}
}

void	print_list_for_env(t_mini *shell, t_env *envs)
{
	if (envs->options_env & 1)
		ft_print_list(&envs->copy_list_env);
	else
		ft_print_list(&shell->list_env);
}
