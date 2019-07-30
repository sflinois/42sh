/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_move_cursor_one_left.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:50:51 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/08 16:32:52 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_term_caps.h"

void	ft_tc_move_cursor_left(void)
{
	char	*res;

	if ((res = tgetstr("le", NULL)) == NULL)
		return ;
	else
		tputs(res, 0, ft_tc_my_outc);
}
