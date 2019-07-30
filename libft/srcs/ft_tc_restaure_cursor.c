/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_restaure_cursor.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:47:21 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/05 15:12:56 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_term_caps.h"

void	ft_tc_restaure_position_cursor(void)
{
	char	*res;

	res = NULL;
	if ((res = tgetstr("rc", NULL)) == NULL)
		return ;
	else
		tputs(res, 0, ft_tc_my_outc);
}
