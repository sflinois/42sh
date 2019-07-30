/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_miss.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/02 13:02:27 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/15 16:32:23 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nb_word(char const *s, char c, char x)
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
		{
			if (s[i] == (x = find_char_in_str(s[i], "\"'")))
			{
				i++;
				while (s[i] && s[i] != x)
					i++;
			}
			if (s[i] != '\0')
				i++;
		}
	}
	return (nb_word);
}

static void		go_to_next_double_quote(char const *s, \
		int *a, int *lenword, char f)
{
	(*a)++;
	(*lenword)++;
	while (s[*a] && s[*a] != f)
	{
		(*a)++;
		(*lenword)++;
	}
}

static int		ft_lenword(char const *s, char c, int *i, int *a)
{
	int		lenword;
	char	f;

	lenword = 0;
	f = '\0';
	while (s[*a] == c && s[*a] != '\0')
	{
		(*a)++;
		(*i)++;
	}
	while (s[*a] != c && s[*a] != '\0')
	{
		if (s[*a] == (f = find_char_in_str(s[*a], "\"'")))
		{
			go_to_next_double_quote(s, a, &lenword, f);
		}
		if (s && s[*a] != '\0')
		{
			(*a)++;
			lenword++;
		}
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
	ft_bzero(str, sizeof(char) * lenword + 1);
	while (j < lenword)
		str[j++] = s[(*i)++];
	(*i)++;
	str[j] = '\0';
	return (str);
}

char			**ft_strsplit_miss(char const *s, char c)
{
	char	**tab;
	int		a;
	int		i;
	int		j;
	int		nb_words;

	i = 0;
	j = 0;
	a = 0;
	if (!s)
		return (NULL);
	nb_words = ft_nb_word(s, c, '\0');
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
