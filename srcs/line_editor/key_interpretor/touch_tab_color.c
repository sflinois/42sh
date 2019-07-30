/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   touch_tab_color.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 17:56:01 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/04/02 17:58:59 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

static int  define_type_file(mode_t mode, t_comp *comp)
{
	if ((S_ISLNK(mode)) != 0)
		comp->color = F_MAG;
	else if (S_ISDIR(mode))
	{
		if ((comp->line = ft_strjoinfree(comp->line, "/", 1)) == NULL)
			return (MALLOC_FAIL);
		comp->color = F_CYN;
	}
	else if (S_ISCHR(mode))
		comp->color = F_BLU "\e[43m";
	else if (S_ISBLK(mode))
		comp->color = F_BLU "\e[46m";
	else if (S_ISSOCK(mode))
		comp->color = F_BLK "\e[41m";
	else
		comp->color = NULL;
	return (SUCCESS);
}

int			add_color_file(t_comp *comp, char *dir, int *ret)
{
	struct stat s;
	char        *path;

	path = NULL;
	if ((path = ft_strjoin(dir, "/")) == NULL)
	{
		free_list_completion(&comp);
		return (MALLOC_FAIL);
	}
	else if ((path = ft_strjoinfree(path, comp->line, 1)) == NULL)
	{
		free_list_completion(&comp);
		return (MALLOC_FAIL);
	}
	lstat(path, &s);
	if ((define_type_file(s.st_mode, comp)) == MALLOC_FAIL)
	{
		free_list_completion(&comp);
		return (MALLOC_FAIL);
	}
	*ret = SUCCESS;
	return (SUCCESS);
}
