/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_clean_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:49:57 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/08 16:21:15 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_term_caps.h"

void	ft_tc_clean_screen(void)
{
	char	*res;

	if ((res = tgetstr("cl", NULL)) == NULL)
		return ;
	else
		tputs(res, 0, ft_tc_my_outc);
}
