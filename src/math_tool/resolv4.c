/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolv4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 08:46:36 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/08 15:32:02 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	resolv44(t_polynom *eq, double d1)
{
	if (eq->p == 0.0)
	{
		if (eq->s2 == DBL_MAX)
			eq->s2 = 0.5 * d1 - eq->q2;
		else if (eq->s3 == DBL_MAX)
			eq->s3 = 0.5 * d1 - eq->q2;
	}
	else if (eq->p > 0.0)
	{
		eq->p = sqrt(eq->p);
		if (eq->s2 == DBL_MAX && eq->s3 == DBL_MAX && eq->s4 == DBL_MAX)
		{
			eq->s2 = 0.5 * (d1 + eq->p) + eq->q2;
			eq->s3 = 0.5 * (d1 - eq->p) + eq->q2;
		}
		else if (eq->s3 == DBL_MAX && eq->s4 == DBL_MAX)
		{
			eq->s3 = 0.5 * (d1 + eq->p) + eq->q2;
			eq->s4 = 0.5 * (d1 - eq->p) + eq->q2;
		}
	}
}

void	resolv43(t_polynom *eq, double z, double d1, double d2)
{
	eq->i = 0;
	eq->q1 = d1 * d1;
	eq->q2 = -0.25 * eq->a3;
	eq->p = eq->q1 - 4.0 * (z - d2);
	if (eq->p == 0.0)
		eq->s1 = -0.5 * d1 - eq->q2;
	else if (eq->p > 0.0)
	{
		eq->p = sqrt(eq->p);
		eq->s1 = -0.5 * (d1 + eq->p) + eq->q2;
		eq->s2 = -0.5 * (d1 - eq->p) + eq->q2;
	}
	eq->p = eq->q1 - 4.0 * (z + d2);
	resolv44(eq, d1);
}

void	resolv42(t_polynom *eq, double z)
{
	double d1;
	double d2;

	d1 = 2.0 * z - eq->p;
	if (d1 < 0.0)
	{
		if (d1 > -0.0000000001)
			d1 = 0.0;
		else
			return ;
	}
	if (d1 < 0.00000000001)
	{
		d2 = z * z - eq->r;
		if (d2 < 0.0)
			return ;
		d2 = sqrt(d2);
	}
	else
	{
		d1 = sqrt(d1);
		d2 = 0.5 * eq->q / d1;
	}
	resolv43(eq, z, d1, d2);
}

void	resolv4(t_polynom *eq)
{
	double		a32;
	t_polynom	cubic;
	double		z;

	if (eq->a4 != 1.0)
	{
		eq->a3 /= eq->a4;
		eq->a2 /= eq->a4;
		eq->a1 /= eq->a4;
		eq->a0 /= eq->a4;
	}
	a32 = eq->a3 * eq->a3;
	eq->p = -0.375 * a32 + eq->a2;
	eq->q = 0.125 * a32 * eq->a3 - 0.5 * eq->a3 * eq->a2 + eq->a1;
	eq->r = -0.01171875 * a32 * a32 + 0.0625 * a32 * eq->a2
			- 0.25 * eq->a3 * eq->a1 + eq->a0;
	init_polynom(&cubic);
	cubic.a3 = 1.0;
	cubic.a2 = -0.5 * eq->p;
	cubic.a1 = -eq->r;
	cubic.a0 = 0.5 * eq->r * eq->p - 0.125 * eq->q * eq->q;
	resolv3(&cubic);
	if ((z = cubic.s1) != DBL_MAX)
		if (z != DBL_MAX)
			resolv42(eq, z);
}
