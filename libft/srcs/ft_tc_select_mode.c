/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_select_mode.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:54:32 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/08 17:35:43 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_term_caps.h"

void	ft_tc_select_mode(void)
{
	char	*res;

	if ((res = tgetstr("mr", NULL)) == NULL)
	{
		ft_putendl("lol");
		return ;
	}
	else
		tputs(res, 0, ft_tc_my_outc);
}
