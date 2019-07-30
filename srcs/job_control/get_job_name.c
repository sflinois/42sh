/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 15:07:29 by ljoly             #+#    #+#             */
/*   Updated: 2019/03/28 12:23:57 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static int		get_name(t_ast *ast, char *name)
{
	int			len;
	t_lst_tkn	*tmp;

	len = 0;
	if (ast->left)
	{
		len += get_name(ast->left, name);
	}
	if (ast->token)
	{
		tmp = ast->token;
		while (tmp)
		{
			ft_strcpy(name + len, tmp->order);
			name[len + ft_strlen(tmp->order)] = ' ';
			len += ft_strlen(tmp->order) + 1;
			tmp = tmp->next;
		}
	}
	if (ast->right)
	{
		len += get_name(ast->right, name + len);
	}
	return (len);
}

static int		get_job_len(t_ast *ast)
{
	int			len;
	t_lst_tkn	*tmp;

	len = 0;
	if (ast->left)
	{
		len += get_job_len(ast->left);
	}
	if (ast->token)
	{
		tmp = ast->token;
		while (tmp)
		{
			len += ft_strlen(tmp->order) + 1;
			tmp = tmp->next;
		}
	}
	if (ast->right)
	{
		len += get_job_len(ast->right);
	}
	return (len);
}

/*
** Get job name from ast
*/

char			*get_job_name(t_ast *ast)
{
	char		*name;
	int			len;

	len = get_job_len(ast);
	name = (char*)ft_memalloc(sizeof(char) * len);
	get_name(ast, name);
	name[len] = '\0';
	return (name);
}
