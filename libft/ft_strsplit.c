/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:38:23 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/09 18:06:50 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t		count_word(char const *s, char c)
{
	size_t		size;
	char const	*ps;

	size = 0;
	ps = s;
	while (*ps)
	{
		while (*ps == c)
			ps++;
		if (*ps != c && *ps)
		{
			size++;
			while (*ps != c && *ps)
				ps++;
		}
	}
	return (size);
}

static char			*fill_tab(char const **s, char c, char *tab)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	while ((*s)[i] != c)
		i++;
	if (!(tab = ft_strnew(i)))
		return (NULL);
	while (**s != c && **s)
	{
		tab[j++] = **s;
		(*s)++;
	}
	return (tab);
}

char				**ft_strsplit(char const *s, char c)
{
	size_t		word;
	char		**tab;
	size_t		i;

	tab = NULL;
	i = 0;
	if (!s || !c)
		return (NULL);
	word = count_word(s, c);
	if (!(tab = malloc(sizeof(char *) * word + 1)))
		return (NULL);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			tab[i] = fill_tab(&s, c, tab[i]);
			i++;
		}
	}
	if (tab)
		tab[i] = NULL;
	return (tab);
}
