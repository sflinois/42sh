/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_go_to_the_next_same_char.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 16:07:57 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/24 18:10:48 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		go_next_same_char(char *str, int *a, char c)
{
	(*a)++;
	while (str[*a] && str[*a] != c)
	{
		if ((c == '\"') && str[*a] && str[*a] == '\\')
		{
			(*a)++;
			if (str[*a])
				(*a)++;
		}
		else
			(*a)++;
	}
	if (str[*a] != '\0' && str[*a] == c)
		return (1);
	else
		return (-1);
}
