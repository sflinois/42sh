/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchrstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 22:38:42 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/07/02 23:02:25 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strchrstr(char *str, char *str1)
{
	int		i;
	int		j;
	int		x;

	x = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str1[j])
		{
			if (str1[j] == str[i])
				x = 1;
			j++;
		}
		if (x == 0 && str1[j] == '\0')
			return ((int)str[i]);
		j = 0;
		i++;
	}
	return (-1);
}
