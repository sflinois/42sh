/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:21:52 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/10/30 17:00:22 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tmp;
	int		i;
	int		indexstr;

	i = -1;
	indexstr = 0;
	if (!s1 || !s2)
		return (NULL);
	if ((tmp = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1)) == NULL)
		return (NULL);
	while (s1[++i])
		tmp[i] = s1[i];
	while (s2[indexstr])
	{
		tmp[indexstr + i] = s2[indexstr];
		indexstr++;
	}
	tmp[indexstr + i] = '\0';
	return (tmp);
}
