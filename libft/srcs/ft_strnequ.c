/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:30:38 by rkhalfao          #+#    #+#             */
/*   Updated: 2017/12/04 15:42:38 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t	i;
	char	*ss1;
	char	*ss2;

	i = 0;
	ss1 = (char *)s1;
	ss2 = (char *)s2;
	if (!s1 || !s2)
		return (0);
	while ((ss1[i] == ss2[i]) && ss1[i] && ss2[i] && n)
	{
		i++;
		n--;
	}
	if (n == 0)
		return (1);
	if (!(*(ss1 + i)) && !(*(ss2 + i)))
		return (1);
	else
		return (0);
}
