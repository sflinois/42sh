/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_first_step_tab.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:12:40 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/06 15:24:53 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_create_first_step_tab(int x)
{
	char	**tab;

	tab = NULL;
	if (x <= 0)
		return (NULL);
	if ((tab = (char**)malloc(sizeof(char*) * (x + 1))) == NULL)
		return (NULL);
	tab[x] = NULL;
	return (tab);
}
