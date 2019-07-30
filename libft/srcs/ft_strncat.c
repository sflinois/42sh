/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:27:45 by rkhalfao          #+#    #+#             */
/*   Updated: 2017/12/01 21:00:19 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	i1;

	i = 0;
	i1 = 0;
	while (dest[i] != '\0')
		i++;
	if (dest[i] == '\0')
	{
		while (i1 < n && src[i1])
		{
			dest[i] = src[i1];
			i++;
			i1++;
		}
	}
	dest[i] = '\0';
	return (dest);
}
