/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:13:08 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/20 18:25:35 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptr;
	char	*ptr1;
	size_t	i;

	ptr = (char *)src;
	ptr1 = (char *)dest;
	i = 0;
	while (i < n)
	{
		ptr1[i] = ptr[i];
		i++;
	}
	return (dest);
}
