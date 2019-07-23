/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quadric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:18:20 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/13 10:27:44 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_quadric(t_quadric *q)
{
	q->a = 0;
	q->b = 0;
	q->c = 0;
	q->d = 0;
	q->e = 0;
	q->f = 0;
	q->g = 0;
	q->h = 0;
	q->i = 0;
	q->j = 0;
	q->aa = 0;
	q->bb = 0;
	q->cc = 0;
	q->t1 = 0;
	q->t2 = 0;
	q->t = 0;
}

/*
** The function min_solution returns the closest intersection point.
** Therefore the smaller value bertwenn a and b over 0.
*/

double	min_solution(double a, double b)
{
	if (a < E)
		return (-1);
	if (b > E)
		return (b);
	else if (a > E)
		return (a);
	else
		return (-1);
}

/*
** The function quadric solver resolve the general form of a quadratic surface
** defined by the equation :
** F(x, y, z) := A.x^2 + B.y^2 + C.z^2
** 				 + D.x.y + E.x.z + F.y.z + G.x + H.y + I.z + J
** and check if their is an intersection with a ray, with equation form :
** G(x) := a * x + b.
** For solving we use the discriminant method with ∆ = b^2 - 4 * a * c
** and s1 = (-b - √∆) / (2 * a) and s2 = (-b + √∆) / (2 * a)
*/

double	quadric_solver(t_quadric q, t_ray r)
{
	double	delta;

	q.aa = q.a * r.dir[0] * r.dir[0] + q.b * r.dir[1] * r.dir[1]
		+ q.c * r.dir[2] * r.dir[2] + q.d * r.dir[0] * r.dir[1]
		+ q.e * r.dir[0] * r.dir[2] + q.f * r.dir[1] * r.dir[2];
	q.bb = 2 * q.a * r.ori[0] * r.dir[0] + 2 * q.b * r.ori[1] * r.dir[1]
		+ 2 * q.c * r.ori[2] * r.dir[2]
		+ q.d * (r.ori[0] * r.dir[1] + r.ori[1] * r.dir[0])
		+ q.e * (r.ori[0] * r.dir[2] + r.dir[0] * r.ori[2])
		+ q.f * (r.ori[1] * r.dir[2] + r.dir[1] * r.ori[2])
		+ q.g * r.dir[0] + q.h * r.dir[1] + q.i * r.dir[2];
	q.cc = q.a * r.ori[0] * r.ori[0] + q.b * r.ori[1] * r.ori[1]
		+ q.c * r.ori[2] * r.ori[2] + q.d * r.ori[0] * r.ori[1]
		+ q.e * r.ori[0] * r.ori[2] + q.f * r.ori[1] * r.ori[2]
		+ q.g * r.ori[0] + q.h * r.ori[1] + q.i * r.ori[2] + q.j;
	delta = q.bb * q.bb - 4 * q.aa * q.cc;
	if (delta < 0)
		return (-1);
	if (!q.aa)
		return (-q.cc / q.bb);
	q.t1 = (-q.bb + sqrt(delta)) / (2 * q.aa);
	q.t2 = (-q.bb - sqrt(delta)) / (2 * q.aa);
	return (min_solution(q.t1, q.t2));
}

/*
** To get the normal quadric it suffices to find the partial derivative of
** the general quadric equation and find coordinates (𝜕f/𝜕x, 𝜕f/𝜕y, 𝜕f/𝜕z).
*/

void	normalquadric(double normal[4], double point[4], t_quadric q)
{
	normal[3] = 1;
	normal[0] = 2 * q.a * point[0] + q.d * point[1] + q.e * point[2] + q.g;
	normal[1] = 2 * q.b * point[1] + q.d * point[0] + q.f * point[2] + q.h;
	normal[2] = 2 * q.c * point[2] + q.e * point[0] + q.f * point[1] + q.i;
}
