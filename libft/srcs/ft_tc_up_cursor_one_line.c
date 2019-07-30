/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_up_cursor_one_line.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:52:34 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/08 17:27:25 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_term_caps.h"

void	ft_tc_up_cursor_one_line(void)
{
	char	*res;

	if ((res = tgetstr("up", NULL)) == NULL)
		return ;
	else
		tputs(res, 0, ft_tc_my_outc);
}
