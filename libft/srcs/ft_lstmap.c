/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 19:44:32 by rkhalfao          #+#    #+#             */
/*   Updated: 2017/12/06 17:32:25 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;

	if (!lst || !f)
		return (NULL);
	if ((new = ft_lstnew(f(lst)->content, f(lst)->content_size)) == NULL)
		return (NULL);
	tmp = new;
	while (lst->next)
	{
		lst = lst->next;
		if (!(tmp->next = ft_lstnew(f(lst)->content, f(lst)->content_size)))
			return (NULL);
		tmp = tmp->next;
	}
	return (new);
}
