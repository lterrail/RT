/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 08:45:28 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/13 10:34:46 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		detect_degree(t_polynom *eq)
{
	if (!(eq->a4) && !(eq->a3) && !(eq->a2) && !(eq->a1))
		return (0);
	else if (!(eq->a4) && !(eq->a3) && !(eq->a2))
		return (1);
	else if (!(eq->a4) && !(eq->a3))
		return (2);
	else if (!(eq->a4))
		return (3);
	else
		return (4);
}

void	resolv2(t_polynom *eq)
{
	double	dis;

	dis = eq->a1 * eq->a1 - (4 * eq->a2 * eq->a0);
	if (dis < 0.0)
		return ;
	eq->s1 = (-eq->a1 + sqrt(dis)) / (2 * eq->a2);
	eq->s2 = (-eq->a1 - sqrt(dis)) / (2 * eq->a2);
}

void	init_coef(t_polynom *eq)
{
	if (eq->a3 != 1.0)
	{
		eq->a2 /= eq->a3;
		eq->a1 /= eq->a3;
		eq->a0 /= eq->a3;
	}
}

/*
** To resolve cubic equation we use the CARDAN method wich consist on
** a change of variable and it means making to solve quadratic equation.
*/

void	resolv3(t_polynom *eq)
{
	eq->aa2 = eq->a2 * eq->a2;
	eq->q = (eq->aa2 - 3.0 * eq->a1) / 9.0;
	eq->r = (eq->a2 * (eq->aa2 - 4.5 * eq->a1) + 13.5 * eq->a0) / 27.0;
	eq->q3 = eq->q * eq->q * eq->q;
	eq->r2 = eq->r * eq->r;
	eq->d = eq->q3 - eq->r2;
	eq->an = eq->a2 / 3.0;
	if (eq->d >= 0.0)
	{
		eq->d = eq->r / sqrt(eq->q3);
		eq->alpha = acos(eq->d) / 3.0;
		eq->s_q = -2.0 * sqrt(eq->q);
		eq->s1 = eq->s_q * cos(eq->alpha) - eq->an;
		eq->s2 = eq->s_q * cos(eq->alpha + TWO_PI_3) - eq->an;
		eq->s3 = eq->s_q * cos(eq->alpha + TWO_PI_43) - eq->an;
	}
	else
	{
		eq->s_q = pow(sqrt(eq->r2 - eq->q3) + fabs(eq->r), 1.0 / 3.0);
		if (eq->r < 0)
			eq->s1 = (eq->s_q + eq->q / eq->s_q) - eq->an;
		else
			eq->s1 = -(eq->s_q + eq->q / eq->s_q) - eq->an;
	}
}

/*
** The function resolv allow to solve 4 degree equation.
** Using CADRAN method to solve 3 degree and VIETE method
** to solve 4 degree.
*/

void	resolv(t_polynom *eq)
{
	int	degree;

	degree = detect_degree(eq);
	if (degree == 1)
		eq->s1 = -eq->a0 / eq->a1;
	else if (degree == 2)
		resolv2(eq);
	else if (degree == 3)
		resolv3(eq);
	else if (degree == 4)
		resolv4(eq);
}
