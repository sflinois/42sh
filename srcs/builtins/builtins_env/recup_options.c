/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recup_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/14 10:35:21 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/09 16:22:44 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static int	recup_options_env(char **tabb, t_env *envs, int *i, int j)
{
	while ((*i) < envs->nb_arg && tabb[*i][j++] == '-')
	{
		if (tabb[*i][j] == '\0')
			envs->options_env = envs->options_env | 1;
		while (tabb[*i][j])
		{
			if (tabb[*i][j] == 'i')
				envs->options_env = envs->options_env | 1;
			else if (tabb[*i][j] == 'u')
				envs->options_env = envs->options_env | 2;
			else if (tabb[*i][j] == 'v')
				envs->options_env = envs->options_env | 4;
			else if (tabb[*i][j] == 'P')
				envs->options_env = envs->options_env | 8;
			else if (tabb[*i][j] == 'S')
				envs->options_env = envs->options_env | 16;
			else
				return (put_env_illegal_options(tabb, (*i)));
			j++;
		}
		j = 0;
		(*i)++;
	}
	return (0);
}

static int	error_with_u(t_env *envs)
{
	if (envs->options_env & 2)
	{
		if (envs->nb_arg == 2)
			return (error_no_arg_with_unset());
	}
	return (0);
}

int			recup_all_options_env(char **tabb, t_env *envs, int *i)
{
	int		j;

	j = 0;
	while (*i < envs->nb_arg && ft_strcmp(tabb[*i], "env") == 0)
		(*i)++;
	if (envs->nb_arg > (*i))
	{
		if (tabb[*i][j] == '-')
			if (recup_options_env(tabb, envs, i, 0) == USAGE)
				return (USAGE);
		if ((error_with_u(envs)) == USAGE)
			return (USAGE);
	}
	return (0);
}
