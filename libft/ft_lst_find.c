/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 09:02:57 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/12 09:25:35 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_find(t_list **blst, void *data_ref, int (*cmp)())
{
	t_list	*tmp;

	if (!blst)
		return (NULL);
	tmp = *blst;
	while (tmp)
	{
		if (!(*cmp)(tmp->content, data_ref))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
