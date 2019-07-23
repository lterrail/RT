/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cal_point.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:15:00 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/12 09:26:48 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** The function calpoint calcul the coordinates of the hit point.
*/

void	cal_point(t_ray r, double point[4], double d)
{
	point[3] = 1.0;
	point[0] = r.dir[0] * d + r.ori[0];
	point[1] = r.dir[1] * d + r.ori[1];
	point[2] = r.dir[2] * d + r.ori[2];
}
