/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:25:10 by rkhalfao          #+#    #+#             */
/*   Updated: 2017/12/01 20:59:17 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	char		*dptr;
	const char	*sptr;
	size_t		len;
	size_t		dmax;

	dptr = dest;
	sptr = src;
	len = size;
	while (size-- != 0 && *dptr != 0)
		dptr++;
	dmax = dptr - dest;
	size = len - dmax;
	if (!size)
		return (dmax + ft_strlen(sptr));
	while (*sptr != '\0')
	{
		if (size != 1)
		{
			*dptr++ = *sptr;
			size--;
		}
		sptr++;
	}
	*dptr = 0;
	return (dmax + (sptr - src));
}
