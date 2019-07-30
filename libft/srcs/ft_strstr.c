/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:33:08 by rkhalfao          #+#    #+#             */
/*   Updated: 2017/12/02 20:08:47 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		ih;
	int		in;
	char	*save;

	ih = 0;
	save = 0;
	if (needle[ih] == '\0')
		return ((char *)haystack);
	while (haystack[ih] != '\0')
	{
		if (haystack[ih] == needle[0])
		{
			save = (char *)haystack + ih;
			in = 0;
			while (haystack[ih + in] == needle[in])
			{
				if (needle[in + 1] == '\0')
					return (save);
				in++;
			}
			save = 0;
		}
		ih++;
	}
	return (0);
}
