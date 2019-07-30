/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:29:20 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/10/16 11:42:59 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	sizesrc;

	sizesrc = ft_strlen(src);
	i = 0;
	while (i < n)
	{
		if (i < sizesrc)
			dest[i] = src[i];
		else
			dest[i] = 0;
		i++;
	}
	return (dest);
}
