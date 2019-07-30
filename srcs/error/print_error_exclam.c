/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_exclam.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 11:22:54 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/14 16:51:01 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"

int		error_exclamation(void)
{
	ft_putstr_fd("\n21sh :  !: can't call multi expansion `!'", 2);
	return (USAGE);
}

int		error_not_found(void)
{
	ft_putstr_fd("\n21sh : !nb: event not found", 2);
	return (USAGE);
}

int		ambiguous_redirect(void)
{
	ft_putstr_fd("\n21sh : : ambiguous redirect", 2);
	return (USAGE);
}
