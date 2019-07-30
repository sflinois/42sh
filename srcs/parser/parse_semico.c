/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_semico.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 16:48:06 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 11:37:12 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static int		check_first_char(char *str)
{
	if (str[0] == ';')
		return (unexpected_token(";"));
	return (SUCCESS);
}

static int		check_error_str(char *str, int i, int j)
{
	char	f;

	f = '\0';
	while (str[i])
	{
		if (str[i] == (f = find_char_in_str(str[i], "\"'")))
			go_next_same_char(str, &i, f);
		if (str[i] && str[i] == ';')
		{
			j = i + 1;
			if (str[j] == ';')
				return (unexpected_token(";"));
			while (str[j] && str[j] == ' ')
			{
				j++;
				if (str[j] == ';')
					return (unexpected_token(";"));
			}
			j = 0;
		}
		if (str[i])
			i++;
	}
	return (SUCCESS);
}

int				check_if_semico(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if ((check_first_char(str + i) == USAGE || \
			check_error_str(str + i, 0, 0) == USAGE))
	{
		return (USAGE);
	}
	return (SUCCESS);
}
