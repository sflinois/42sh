/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_right_exec.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:32:52 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/06 11:35:00 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_check_right_exec(char *str)
{
	struct stat		s;

	lstat(str, &s);
	if (s.st_mode & S_IXUSR)
		return (1);
	else
		return (0);
}
