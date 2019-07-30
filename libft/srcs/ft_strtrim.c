/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 20:34:42 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/08 11:17:10 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s, int x)
{
	unsigned int	i;
	int				i1;

	if (!s)
		return (NULL);
	i1 = (int)ft_strlen(s) - 1;
	i = 0;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && s[i])
		i++;
	while ((s[i1] == ' ' || s[i1] == '\n' || s[i1] == '\t') \
			&& s[i1] && i1 > (int)i)
		i1--;
	return (ft_strsub(s, i, (i1 - i + 1), x));
}
