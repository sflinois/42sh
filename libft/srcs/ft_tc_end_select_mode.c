/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_end_select_mode.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:55:28 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/08 17:33:18 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_term_caps.h"

void	ft_tc_end_select_mode(void)
{
	char	*res;

	if ((res = tgetstr("me", NULL)) == NULL)
		return ;
	else
		tputs(res, 0, ft_tc_my_outc);
}
