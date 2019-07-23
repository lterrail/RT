/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 17:37:40 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/09 18:09:08 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*blst;

	new = NULL;
	if (!lst || !f)
		return (NULL);
	if (!(new = (*f)(lst)))
		return (NULL);
	blst = new;
	while (lst->next)
	{
		lst = lst->next;
		if (!(new = (*f)(lst)))
			return (NULL);
		ft_lstadd_back(&blst, new);
	}
	return (blst);
}
