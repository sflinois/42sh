/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_space_local.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:20:53 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/01/27 15:06:46 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	delete_space_local(char *str)
{
	int		i;

	i = 0;
	while (str[0] && str[0] == ' ')
	{
		while (str[i])
		{
			str[i] = str[i + 1];
			i++;
		}
		i = 0;
	}
	i = ft_strlen(str) - 1;
	while (i > 0 && str[i] == ' ')
	{
		str[i] = '\0';
		i--;
	}
}
