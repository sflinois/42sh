/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:02:27 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/02/12 09:34:54 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nb_word(char const *s, char c)
{
	int		i;
	int		nb_word;

	i = 0;
	nb_word = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			nb_word++;
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	return (nb_word);
}

static int		ft_lenword(char const *s, char c, int *i, int *a)
{
	int		lenword;

	lenword = 0;
	while (s[*a] == c && s[*a] != '\0')
	{
		(*a)++;
		(*i)++;
	}
	while (s[*a] != c && s[*a] != '\0')
	{
		(*a)++;
		lenword++;
	}
	(*a)++;
	return (lenword);
}

static char		*ft_filltab(char const *s, char c, int *i, int *a)
{
	char	*str;
	int		j;
	int		lenword;

	j = 0;
	lenword = ft_lenword(s, c, i, a);
	if ((str = (char*)malloc(sizeof(*str) * (lenword + 1))) == NULL)
		return (NULL);
	while (j < lenword)
		str[j++] = s[(*i)++];
	(*i)++;
	str[j] = '\0';
	return (str);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		a;
	int		i;
	int		j;
	int		nb_words;

	i = 0;
	j = 0;
	a = 0;
	tab = NULL;
	if (!s)
		return (NULL);
	nb_words = ft_nb_word(s, c);
	if ((tab = (char**)malloc(sizeof(*tab) * (nb_words + 1))) == NULL)
		return (NULL);
	while (j < nb_words)
	{
		if ((tab[j] = ft_filltab(s, c, &i, &a)) == NULL)
		{
			ft_free_tab(tab);
			return (NULL);
		}
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
