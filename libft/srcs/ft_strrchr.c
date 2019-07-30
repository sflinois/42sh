/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:32:55 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/05/23 12:04:51 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*ptr;
	int		i;

	ptr = (char*)str;
	i = 0;
	while (ptr[i])
		i++;
	if (ptr[i] == c)
		return (&ptr[i]);
	while (i >= 0)
	{
		if (ptr[i] == c)
			return (ptr + i);
		i--;
	}
	return (NULL);
}
