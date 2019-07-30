/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:25:48 by rkhalfao          #+#    #+#             */
/*   Updated: 2017/12/05 20:15:51 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ptr;
	int		i;
	int		sizestr;

	i = 0;
	if (s && *f)
	{
		sizestr = ft_strlen(s);
		if ((ptr = (char *)malloc(sizeof(*ptr) * sizestr + 1)) == NULL)
			return (NULL);
		while (i < sizestr)
		{
			ptr[i] = f(s[i]);
			i++;
		}
		ptr[i] = '\0';
		return (ptr);
	}
	return (0);
}
