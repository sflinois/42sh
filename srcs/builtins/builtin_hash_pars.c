/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash_pars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/12 16:01:42 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/12 16:20:20 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

int				pars_hash_args(char **argv, int *reset,
								char **path, int *cmd_index)
{
	int		j;

	j = 1;
	while (argv[j] && *cmd_index == 0)
	{
		if (argv[j][0] == '-')
		{
			if (argv[j][1] == 'r')
				*reset = 1;
			else if (argv[j][1] == 'p')
			{
				*path = ft_strdup(argv[j + 1]);
				if (*path == NULL)
					return (print_hash_error(USAGE, NULL));
				*cmd_index = ++j + 1;
			}
			else
				return (print_hash_error(USAGE, NULL));
		}
		else
			*cmd_index = j;
		j++;
	}
	return (0);
}
