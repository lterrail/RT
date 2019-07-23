/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:45:56 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/08 16:00:21 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const char	*ph;
	const char	*pn;
	size_t		i;

	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (*haystack && len > 0)
	{
		ph = haystack;
		pn = needle;
		i = len;
		while (*ph == *pn && *pn && *ph && i--)
		{
			pn++;
			ph++;
		}
		if (!*pn)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
