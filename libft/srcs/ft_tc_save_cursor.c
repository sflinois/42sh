/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_save_cursor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:45:41 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/08 17:16:49 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term_caps.h"
#include "libft.h"

void	ft_tc_save_position_cursor(void)
{
	char	*res;

	res = NULL;
	if ((res = tgetstr("sc", NULL)) == NULL)
		return ;
	else
		tputs(res, 0, ft_tc_my_outc);
}
