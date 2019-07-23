/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:46:56 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/08 12:26:34 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*new;
	const char	*end;
	char		*pn;

	new = NULL;
	if (!s)
		return (NULL);
	end = s + ft_strlen(s);
	while (*s == ' ' || *s == '\n' || *s == '\t')
		s++;
	while ((*end == ' ' || *end == '\n' || *end == '\t' || !*end) && end > s)
		end--;
	if (!(new = ft_strnew(end - s + 1)))
		return (NULL);
	pn = new;
	while (s <= end)
		*pn++ = *s++;
	return (new);
}
