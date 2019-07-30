/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect_atoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 10:36:49 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/01/23 15:44:00 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int		protect_atoi(const char *str, int protect)
{
	int		i;
	int		rslt;
	int		pon;

	rslt = 0;
	i = 0;
	pon = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || \
			str[i] == '\v' || str[i] == '\f' || str[i] == '\n')
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			pon = -1;
	while ((str[i] >= '0' && str[i] <= '9' && str[i]))
	{
		rslt = rslt * 10 + (str[i++] - 48);
		protect = 1;
	}
	if (protect != 1)
		return (-1);
	if (pon == 1 && rslt > 2147483647)
		return (2147483647);
	if (pon == -1 && rslt > 2147483646)
		return (-2147483646);
	return (rslt * pon);
}
