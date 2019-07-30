/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/03 15:16:53 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/01/22 17:52:56 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char	*ft_fillstr(int n, char *str, unsigned int x)
{
	unsigned int	neg;
	unsigned int	i;
	unsigned int	nb;

	neg = 0;
	i = 0;
	nb = 0;
	if (n < 0)
	{
		neg = 1;
		nb = -n;
		str[i] = '-';
		i++;
	}
	if (neg == 0)
		nb = (unsigned int)n;
	str[x] = '\0';
	while (i < x)
	{
		str[x - 1] = nb % 10 + '0';
		nb = nb / 10;
		x--;
	}
	return (str);
}

static int	ft_sizeint(int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		i++;
	while (n != 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		taille;

	taille = ft_sizeint(n);
	if ((str = (char*)malloc(sizeof(*str) * taille + 1)) == NULL)
		return (NULL);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	return (ft_fillstr(n, str, taille));
}
