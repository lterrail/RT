/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:44:44 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/08 12:07:26 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	end;
	size_t	i;

	end = ft_strlen(dest);
	i = 0;
	while (src[i] && i < n)
		dest[end++] = src[i++];
	dest[end] = '\0';
	return (dest);
}
