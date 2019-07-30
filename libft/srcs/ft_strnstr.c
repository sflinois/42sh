/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:31:40 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/05/23 12:03:41 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	ih;
	size_t	in;
	char	*save;

	ih = 0;
	save = 0;
	if (needle[ih] == '\0')
		return ((char *)haystack);
	while (haystack[ih] && ih < len)
	{
		if (haystack[ih] == needle[0])
		{
			save = (char *)haystack + ih;
			in = 0;
			while (haystack[ih + in] == needle[in] && ih + in < len)
			{
				if (needle[in + 1] == '\0')
					return (save);
				in++;
			}
			save = 0;
		}
		ih++;
	}
	return (NULL);
}
