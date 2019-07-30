/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tc_clear_all_after_cursor.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:38:10 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/12 13:56:02 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_term_caps.h"
#include "libft.h"

void	ft_tc_clear_after_cursor(void)
{
	char	*res;

	res = NULL;
	if ((res = tgetstr("cd", NULL)) == NULL)
		return ;
	else
		tputs(res, 0, ft_tc_my_outc);
}
