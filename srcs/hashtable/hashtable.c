/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 13:56:51 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/15 12:10:37 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "ft_minishell.h"

void			ht_init(t_ht **ht)
{
	ft_bzero(ht, sizeof(t_ht*) * HT_SIZE);
}

char			*ht_search(t_ht **ht, char *cmd)
{
	int		i;
	t_ht	*tmp;

	i = ht_hash(cmd) % HT_SIZE;
	tmp = ht[i];
	if (tmp)
		return (tmp->path);
	return (NULL);
}

void			ht_insert(t_ht **ht, char *cmd, char *path)
{
	int		i;

	i = ht_hash(cmd) % HT_SIZE;
	if (ht[i])
	{
		free(ht[i]->cmd);
		free(ht[i]->path);
		free(ht[i]);
	}
	ht[i] = ft_memalloc(sizeof(t_ht));
	ht[i]->next = NULL;
	ht[i]->hits = 0;
	ht[i]->cmd = ft_strdup(cmd);
	ht[i]->path = ft_strdup(path);
}

void			ht_clear(t_ht **ht)
{
	int		i;

	i = 0;
	while (i < HT_SIZE)
	{
		if (ht[i])
		{
			free(ht[i]->cmd);
			free(ht[i]->path);
			ht[i]->cmd = NULL;
			ht[i]->path = NULL;
			ht[i]->hits = 0;
			free(ht[i]);
			ht[i] = NULL;
		}
		i++;
	}
}

/*
** Implementation of djb2 hash algorithm (hash * 33 + c)
*/

unsigned long	ht_hash(char *cmd)
{
	unsigned long	hash;
	int				c;

	hash = 5381;
	while ((c = *cmd++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}
