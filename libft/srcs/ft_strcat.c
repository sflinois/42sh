/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:15:09 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/06 16:35:51 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	int i;
	int i1;

	i = 0;
	i1 = 0;
	while (dest[i] != '\0')
		i++;
	if (dest[i] == '\0')
	{
		while (src[i1] != '\0')
		{
			dest[i] = src[i1];
			i++;
			i1++;
		}
		dest[i] = '\0';
	}
	return (dest);
}
