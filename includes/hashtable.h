/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:29:26 by sflinois          #+#    #+#             */
/*   Updated: 2019/03/31 18:35:05 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include <stdio.h>
# define HT_SIZE 8192

typedef struct		s_ht
{
	int				hits;
	char			*cmd;
	char			*path;
	struct s_ht		*next;
}					t_ht;

void				ht_init(t_ht **ht);
char				*ht_search(t_ht **ht, char *cmd);
void				ht_insert(t_ht **ht, char *cmd, char *path);
void				ht_clear(t_ht **ht);
void				print_hashtable(t_ht *ht[HT_SIZE]);
unsigned long		ht_hash(char *cmd);
#endif
