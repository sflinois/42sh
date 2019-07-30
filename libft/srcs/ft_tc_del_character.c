/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_del_character.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:56:40 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 16:40:41 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_term_caps.h"

void	ft_tc_del_the_carac(void)
{
	char	*res;

	if ((res = tgetstr("dc", NULL)) == NULL)
		return ;
	else
		tputs(res, 0, ft_tc_my_outc);
}
