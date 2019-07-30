/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 09:09:10 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/09 13:24:58 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

t_err	builtin_set(t_mini *shell)
{
	int		i;

	i = 1;
	if (i == shell->nb_arg)
		ft_print_list(&shell->list_set);
	else
		return (print_error_illegal_options());
	return (SUCCESS);
}
