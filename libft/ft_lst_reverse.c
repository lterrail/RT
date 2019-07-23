/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 18:14:33 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/12 08:37:11 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst_reverse(t_list **blst)
{
	t_list	*current;
	t_list	*next;
	t_list	*prev;

	if (!blst)
		return ;
	current = *blst;
	next = current->next;
	prev = current;
	current->next = NULL;
	while (next)
	{
		prev = current;
		current = next;
		next = current->next;
		current->next = prev;
	}
	*blst = current;
}
