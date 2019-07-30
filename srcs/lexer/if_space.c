/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/08 14:03:33 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 10:59:01 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lexer.h"

int		handle_space(char **buffer, t_lst_tkn **lst)
{
	(void)lst;
	while (**buffer && **buffer == ' ')
		(*buffer)++;
	return (0);
}
