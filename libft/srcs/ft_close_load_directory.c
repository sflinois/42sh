/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_load_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 11:28:35 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/08 11:09:28 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_close_load_directory(DIR *rep)
{
	if ((closedir(rep)) == -1)
		ft_putendl("Error : can't close directory");
}
