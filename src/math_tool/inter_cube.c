/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_cube.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 13:27:41 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/13 19:51:12 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** These functions allow to find the intersection point between a ray
** and an holed cube and then calcul the coordinates of the normal
** vector at the hit point.
*/

/*
** The function calc_coef calculates the polynomial coefficients
** of the equation which define the intersection between an holed cube :
** F(x, y, z) := x^4 + y^4 + z^4 - 5 * (x^2 + y^2 + z^2) + 11.8
** and a ray :
** G(x) := a * x + b
*/

static void	calc_coeff(t_polynom *p, t_ray r)
{
	init_polynom(p);
	p->a4 = pow(r.dir[0], 4) + pow(r.dir[1], 4) + pow(r.dir[2], 4);
	p->a3 = 4 * (pow(r.dir[0], 3) * r.ori[0] + pow(r.dir[1], 3) * r.ori[1]
			+ pow(r.dir[2], 3) * r.ori[2]);
	p->a2 = 6 * (pow(r.dir[0], 2) * pow(r.ori[0], 2)
			+ pow(r.dir[1], 2) * pow(r.ori[1], 2)
			+ pow(r.dir[2], 2) * pow(r.ori[2], 2))
			- 5 * (pow(r.dir[0], 2) + pow(r.dir[1], 2) + pow(r.dir[2], 2));
	p->a1 = 4 * (pow(r.ori[0], 3) * r.dir[0] + pow(r.ori[1], 3) * r.dir[1]
			+ pow(r.ori[2], 3) * r.dir[2])
			- 10 * (r.dir[0] * r.ori[0] + r.dir[1] * r.ori[1]
			+ r.dir[2] * r.ori[2]);
	p->a0 = pow(r.ori[0], 4) + pow(r.ori[1], 4) + pow(r.ori[2], 4)
			- 5 * (pow(r.ori[0], 2) + pow(r.ori[1], 2) + pow(r.ori[2], 2))
			+ 9.8;
}

/*
** To calculate the normal coordinates we find the partial derivative of
** the hole cube equation and find coordinates (𝜕f/𝜕x, 𝜕f/𝜕y, 𝜕f/𝜕z)
*/

void		normal_cube(double normal[4], double p[4])
{
	normal[0] = 4 * pow(p[0], 3) - 10 * p[0];
	normal[1] = 4 * pow(p[1], 3) - 10 * p[1];
	normal[2] = 4 * pow(p[2], 3) - 10 * p[2];
	normal[3] = 1;
}

/*
** The inter_cube function checks if their is an intersection between the
** holed cube and the ray.
** It returns respectively 0 if their is no intersection,
** a double over 0 if their is an intersection and then find the coordinates of
** this point and the normal coordinates at this point.
*/

double		inter_cube(t_ray r, t_obj *s)
{
	t_polynom	p;
	t_ray		r2;
	double		res;
	double		tmp[4];
	double		tmp2[4];

	inv_transformation(&s->t, r2.ori, r.ori);
	point_matrix(r2.dir, r.dir, s->t.inv_rotation);
	calc_coeff(&p, r2);
	resolv(&p);
	res = closest_inter(p);
	if (res < E)
		return (0);
	cal_point(r2, tmp, res);
	normal_cube(tmp2, tmp);
	point_matrix(s->normal2, tmp2, s->t.rotation);
	if (dot_product(r2.dir, tmp2) < 0 && s->reflect == 0.0)
		double_vec(tmp2, -1, tmp2);
	normalize(tmp2);
	transformation(&s->t, s->point, tmp);
	point_matrix(s->normal, tmp2, s->t.rotation);
	normalize(s->normal);
	return (res);
}
