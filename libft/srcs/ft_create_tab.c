/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tab.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 13:50:57 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/01/29 11:10:33 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_create_tab(int l, int c)
{
	char	**new_tab;
	int		i;

	i = 0;
	if ((new_tab = (char**)malloc(sizeof(*new_tab) * (l + 1))) == NULL)
		return (NULL);
	while (i < l)
	{
		if (((new_tab[i]) = (char*)malloc(sizeof(char) * (c + 1))) == NULL)
			return (NULL);
		ft_bzero((new_tab[i]), (size_t)c);
		i++;
	}
	new_tab[i] = NULL;
	return (new_tab);
}
