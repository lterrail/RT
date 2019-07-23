/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_inter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 11:31:02 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/12 15:51:45 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	closest_inter(t_polynom p)
{
	double	min;

	min = DBL_MAX;
	if (p.s1 > 0 && p.s1 < min)
		min = p.s1;
	if (p.s2 > 0 && p.s2 < min)
		min = p.s2;
	if (p.s3 > 0 && p.s3 < min)
		min = p.s3;
	if (p.s4 > 0 && p.s4 < min)
		min = p.s4;
	if (min == DBL_MAX)
		return (-1);
	return (min);
}
