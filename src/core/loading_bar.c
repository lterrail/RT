/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_bar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 18:26:59 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/19 18:28:58 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_bar(t_bar *bar, t_all *all)
{
	bar->ij[0] = all->i;
	all->i += (SIZE_H / 4);
	bar->max = all->i;
	bar->dlmax = SIZE_H * SIZE_W + SIZE_W;
}

void		manage_bar(t_bar bar)
{
	bar.dl = bar.ij[0] * SIZE_W + bar.ij[1];
	print_bar('|', bar);
}
