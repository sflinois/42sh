/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 11:09:04 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/10/16 11:40:11 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcdup(const char *src, int c)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!((tmp = (char*)malloc(sizeof(*tmp) * ft_strlen(src) + 1))))
		return (NULL);
	while (src[i] != c && src[i])
		i++;
	while (src[i + j] != '\0')
	{
		tmp[j] = src[i + j];
		j++;
	}
	tmp[j] = '\0';
	return (tmp);
}
