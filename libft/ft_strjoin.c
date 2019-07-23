/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:43:31 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/08 12:06:04 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	new = NULL;
	if (s1 && !s2)
		return (!(new = ft_strdup(s1))) ? NULL : new;
	else if (!s1 && s2)
		return (!(new = ft_strdup(s2))) ? NULL : new;
	else if (s1 && s2)
		return (!(new = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1))) ? NULL
		: ft_strcat(ft_strcpy(new, s1), s2);
	return (NULL);
}
