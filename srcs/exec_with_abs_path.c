/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_with_abs_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 12:03:18 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/12 14:43:56 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minishell.h"
#include "error.h"

static int	check_if_have_the_right(char *str)
{
	struct stat		s;

	lstat(str, &s);
	if (s.st_mode & S_IXUSR)
	{
		return (SUCCESS);
	}
	else
	{
		ft_putstr("21sh: ");
		ft_putstr(str);
		ft_putendl(": Permission denied");
	}
	return (USAGE);
}

int			modifie_absolute_path(t_mini *shell, char *str, t_listenv **list, \
		char **tabb)
{
	if ((access(str, F_OK)) != 0)
	{
		ft_putstr("21sh: ");
		ft_putstr(str);
		ft_putendl(": No such file or directory");
		return (USAGE);
	}
	else if (check_if_have_the_right(str) == USAGE)
	{
		return (USAGE);
	}
	else
	{
		shell->good_path = ft_strdup(str);
		go_for_fork(shell, tabb, list);
		return (SUCCESS);
	}
}
