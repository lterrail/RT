/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_at.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 08:42:32 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/12 08:46:36 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lst_at(t_list **blst, unsigned int n)
{
	t_list	*tmp;

	if (!blst)
		return (NULL);
	tmp = *blst;
	while (n--)
		tmp = tmp->next;
	return (tmp);
}
