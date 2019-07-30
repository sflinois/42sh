/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:14:03 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/10/22 10:30:33 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*swp;

	swp = NULL;
	if (n)
		swp = malloc(n);
	if (swp)
	{
		ft_memcpy(swp, src, n);
		ft_memcpy(dest, swp, n);
		free(swp);
	}
	return (dest);
}
