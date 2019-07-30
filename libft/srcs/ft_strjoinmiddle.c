/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinmiddle.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 15:37:23 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/29 17:20:10 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinmiddle(char *s1, char *s2, int c, int d)
{
	int		i;
	int		j;
	int		l;
	char	*str;

	str = NULL;
	i = 0;
	j = 0;
	l = 0;
	if ((str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))) == NULL)
		return (NULL);
	while (s1[i] && c > 0)
	{
		str[j++] = s1[i++];
		c--;
	}
	while (d-- > 0 && s1[i])
		i++;
	while (s2[l])
		str[j++] = s2[l++];
	while (s1[i])
		str[j++] = s1[i++];
	free(s1);
	return (str);
}
