/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_full_space.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 12:17:35 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/10 18:09:39 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	check_full_space(char *str, int f)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			i++;
		else
			return (FALSE);
	}
	if (f == 1)
		free(str);
	return (TRUE);
}
