/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   next_char_without_space.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 13:28:28 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 16:38:57 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		next_c_wo_space(char *str, char *check)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str || !check)
		return (-1);
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && check[j])
	{
		if (check[j] == str[i])
			return (1);
		j++;
	}
	return (0);
}
