/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:09:05 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/26 15:12:01 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char **tabb)
{
	int		i;

	i = 0;
	if (!(tabb) || !(*tabb))
		return ;
	while (tabb[i])
	{
		free(tabb[i]);
		i++;
	}
	free(tabb);
}
