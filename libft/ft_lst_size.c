/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 08:37:21 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/12 09:31:20 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lst_size(t_list *lst)
{
	unsigned int	size;

	size = 0;
	if (!lst)
		return (-1);
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}
