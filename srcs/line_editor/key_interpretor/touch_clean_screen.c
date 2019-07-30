/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_clean_screen.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/20 09:44:10 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 19:35:17 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include <term.h>

int		go_clean_screen(t_le *ledit)
{
	int		i;

	i = 0;
	ft_tc_clean_screen();
	print_my_prompt(ledit);
	if (ledit->buffer[i] != '\0')
	{
		while (ledit->buffer[i])
		{
			ft_putchar(ledit->buffer[i]);
			if (ledit->buffer[i] == '\n')
			{
				
				if (ledit->i_return == 0)
					ft_putstr("\x1B[32m");
				else
					ft_putstr("\x1B[31m");
				ft_putstr("         >\033[0m");
			
			}
			i++;
		}
	}
	ledit->index_buffer = ft_strlen(ledit->buffer);
	return (0);
}
