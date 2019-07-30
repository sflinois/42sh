/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:33:48 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/01/16 17:08:54 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len, int x)
{
	char	*str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if ((str = (char *)malloc(sizeof(*str) * (len + 1))) == NULL)
		return (NULL);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
		str[i++] = s[start++];
	if (x == 1)
		free((char*)s);
	return (str);
}
