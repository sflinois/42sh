/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_clean_line_aft_cursor.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:23:08 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 16:41:19 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term_caps.h"
#include "libft.h"

void	ft_tc_clean_line_aft_cursor(void)
{
	char	*res;

	if ((res = tgetstr("cl", NULL)) == NULL)
		return ;
	else
		tputs(res, 0, ft_tc_my_outc);
}
