/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:43:59 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/07 12:20:20 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const unsigned char	*ps;
	unsigned char		*pd;
	unsigned char		k;
	size_t				i;

	k = c;
	ps = src;
	pd = dest;
	i = 0;
	while (i++ < n)
	{
		*pd = *ps++;
		if (*pd++ == k)
			return (dest + i);
	}
	return (NULL);
}
