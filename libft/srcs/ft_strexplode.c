/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strexplode1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 12:31:23 by rkhalfao          #+#    #+#             */
/*   Updated: 2018/11/05 12:35:09 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_str(char c, char *str)
{
	int		i;

	if (c == '\0')
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_count_words(const char *str, char *c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_in_str(str[i], c))
			i++;
		else
		{
			count++;
			while (ft_in_str(str[i], c) == 0 && str[i] != '\0')
				i++;
		}
	}
	return (count);
}

static int	ft_ct(const char *str, char *c)
{
	int i;

	i = 0;
	while (ft_in_str(str[i], c) == 0 && str[i] != '\0')
		i++;
	return (i);
}

static char	**ft_explode(char const *s, char *c)
{
	char	**tab;
	int		i;
	int		j;
	int		k;

	if (!(tab = (char**)malloc(sizeof(*tab) * (ft_count_words(s, c) + 1))))
		return (NULL);
	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (ft_in_str(s[i], c))
			i++;
		else
		{
			if (!(tab[k] = (char*)malloc(sizeof(char) * (ft_ct(s + i, c) + 1))))
				return (NULL);
			j = 0;
			while (ft_in_str(s[i], c) == 0 && s[i] != '\0')
				tab[k][j++] = s[i++];
			tab[k++][j] = '\0';
		}
	}
	tab[k] = 0;
	return (tab);
}

extern char	**ft_strexplode(char const *s, char *c)
{
	if (!s || *s == '\0')
		return (NULL);
	else
		return (ft_explode(s, c));
}
