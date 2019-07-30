/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_percent_diez.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/23 10:13:52 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:17:27 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"

int		dollar_percent(t_mini *shell, t_le *ledit, int *i, int exist)
{
	(*i)++;
	return (simple_dollar(&shell->list_set, ledit, i, exist));
}

int		dollar_double_percent(t_mini *shell, t_le *ledit, int *i, int exist)
{
	(*i) = (*i) + 2;
	return (simple_dollar(&shell->list_set, ledit, i, exist));
}

int		dollar_diez(t_mini *shell, t_le *ledit, int *i, int exist)
{
	(*i)++;
	return (simple_dollar(&shell->list_set, ledit, i, exist));
}

int		dollar_double_diez(t_mini *shell, t_le *ledit, int *i, int exist)
{
	(*i) = (*i) + 2;
	return (simple_dollar(&shell->list_set, ledit, i, exist));
}
