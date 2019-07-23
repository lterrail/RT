/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:44:50 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/08 11:33:28 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*pd;
	const unsigned char	*ps;

	i = 0;
	pd = dest;
	ps = src;
	if (pd < ps)
		while (i++ < n)
			*pd++ = *ps++;
	else
		while (n--)
			*(pd + n) = *(ps + n);
	return (dest);
}
