/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 15:03:31 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/12 09:30:40 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *s1, char *s2, int i)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (i == 1)
		free(s1);
	else if (i == 2)
		free(s2);
	else if (i == 3)
	{
		free(s1);
		free(s2);
	}
	if (str == NULL)
		return (NULL);
	return (str);
}
