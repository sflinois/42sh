/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:26:32 by rkhalfao          #+#    #+#             */
/*   Updated: 2017/12/02 20:10:30 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	sisestr;
	char			*mapi;

	if (!s)
		return (NULL);
	sisestr = ft_strlen(s);
	if ((mapi = (char *)malloc(sizeof(*mapi) * sisestr + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i < sisestr)
	{
		mapi[i] = f(i, s[i]);
		i++;
	}
	mapi[i] = '\0';
	return (mapi);
}
