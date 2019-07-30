/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_inhib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhalfao <rkhalfao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:14:28 by rkhalfao          #+#    #+#             */
/*   Updated: 2019/03/02 13:21:57 by rkhalfao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_lineedit.h"
#include "error.h"

t_bool			parse_full_backslashn(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (str[i] && str[i] == '\\')
	{
		i++;
		if (str[i] && (str[i] == '\n' || str[i] == ' '))
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
		}
		else
			return (TRUE);
	}
	if (str[i] == '\0')
		return (FALSE);
	return (TRUE);
}

static t_bool	check_last_charac(char *str, int i)
{
	if (str[i] == '\0')
		i--;
	if (i != (int)ft_strlen(str) - 1)
		return (TRUE);
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || (str[i] == 92 \
	&& if_echap_and(str, i, 0) == FALSE)))
		i--;
	if (str[i] == '|')
		return (FALSE);
	else if (str[i] == '&' && str[i - 1] == '&' \
			&& if_echap_and(str, i - 1, 0) == FALSE)
		return (FALSE);
	return (TRUE);
}

t_bool			check_quote_close(char *str, int *i)
{
	char	f;

	f = '\0';
	if (str[*i] && str[*i] == (f = find_char_in_str(str[*i], "\"'")))
	{
		if (if_echap_and(str, *i, 0) == FALSE \
		&& go_next_same_char(str, i, f) == -1)
			return (FALSE);
	}
	return (TRUE);
}

static void		copy_str_check(char *str, char *str_check)
{
	int		i;
	int		a;
	int		j;

	a = ft_strlen(str) - 1;
	i = 0;
	j = 0;
	while (str[i] && str[i] == ' ')
		i++;
	while (a > 0 && str[a] && str[a] == ' ')
		a--;
	a++;
	while (i < a && str[i])
		str_check[j++] = str[i++];
}

t_bool			verif_miss_inhib(char *str, int i)
{
	char	str_check[520];

	ft_bzero(&str_check, sizeof(char) * 520);
	copy_str_check(str, str_check);
	while (str_check[i])
	{
		if ((check_quote_close(str_check, &i)) == FALSE)
			return (FALSE);
		else if (str[i] && str[i] == 92)
		{
			i++;
			if (str_check[i])
				i++;
			else
				return (FALSE);
		}
		else
			i++;
	}
	return (check_last_charac(str_check, i));
}
