/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsplit_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 14:23:52 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/06 16:29:00 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*unsplit_the_tab(char **tabb)
{
	char	*str;
	int		i;

	i = 1;
	str = ft_strdup(tabb[0]);
	str = ft_strjoinfree(str, " ", 1);
	while (tabb[i])
	{
		if (tabb[i + 1] != NULL)
		{
			str = ft_strjoinfree(str, tabb[i], 1);
			str = ft_strjoinfree(str, " ", 1);
		}
		else
			str = ft_strjoinfree(str, tabb[i], 1);
		i++;
	}
	ft_free_tab(tabb);
	return (str);
}

char	*ft_unsplit_tab(char **tabb)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	if (!*tabb)
		return (NULL);
	while (tabb[i])
		i++;
	if (i == 1)
	{
		str = ft_strdup(tabb[0]);
		ft_free_tab(tabb);
		return (str);
	}
	else if (i > 1)
		str = unsplit_the_tab(tabb);
	return (str);
}
