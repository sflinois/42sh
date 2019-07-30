/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:32:59 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/10/16 11:43:31 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, int len)
{
	char	*tmp;

	if ((tmp = ft_strnew(len)) == NULL)
		return (NULL);
	tmp = ft_strncpy(tmp, src, len);
	return (tmp);
}
