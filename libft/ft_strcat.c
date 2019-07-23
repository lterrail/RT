/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:37:43 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/08 12:01:11 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	end;
	size_t	i;

	i = 0;
	end = ft_strlen(dest);
	while (src[i])
		dest[end++] = src[i++];
	dest[end] = '\0';
	return (dest);
}
