/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_move_cursor_one_right.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:49:01 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/05 15:11:50 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_term_caps.h"

void	ft_tc_move_cursor_one_right(void)
{
	char	*res;

	if ((res = tgetstr("nd", NULL)) == NULL)
		return ;
	else
		tputs(res, 0, ft_tc_my_outc);
}
