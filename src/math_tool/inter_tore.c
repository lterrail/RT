/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_tore.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 11:48:22 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/13 19:49:43 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** These functions allow to find the intersection point between a ray
** and a torus and then calcul the coordinates of the normal
** vector at the hit point.
*/

/*
** The function calc_coef calculates the polynomial coefficients
** of the equation which define the intersection between a torus :
** F(x, y, z) := (x^2 + y^2 + z^2 + r_tore^2 - r^2)^2 - 4 * r_tore^2(x^2 + z^2)
** and a ray :
** G(x) := a * x + b
*/

static void	calc_coeff(t_polynom *p, t_ray r2, t_obj *s)
{
	t_tore	t;

	init_polynom(p);
	t.tmp_a = r2.dir[0] * r2.dir[0] + r2.dir[1] * r2.dir[1]
			+ r2.dir[2] * r2.dir[2];
	t.tmp_b = 2.0 * (r2.dir[0] * r2.ori[0] + r2.dir[1] * r2.ori[1]
			+ r2.dir[2] * r2.ori[2]);
	t.tmp_c = r2.ori[0] * r2.ori[0] + r2.ori[1] * r2.ori[1]
			+ r2.ori[2] * r2.ori[2]
		+ s->r_tore * s->r_tore - s->rayon * s->rayon;
	t.tmp = 4.0 * s->r_tore * s->r_tore;
	t.tmp_d = t.tmp * (r2.dir[0] * r2.dir[0] + r2.dir[2] * r2.dir[2]);
	t.tmp_e = t.tmp * 2 * (r2.dir[0] * r2.ori[0]
			+ r2.dir[2] * r2.ori[2]);
	t.tmp_f = t.tmp * (r2.ori[0] * r2.ori[0] + r2.ori[2] * r2.ori[2]);
	p->a4 = t.tmp_a * t.tmp_a;
	p->a3 = 2.0 * t.tmp_a * t.tmp_b;
	p->a2 = 2.0 * t.tmp_a * t.tmp_c + t.tmp_b * t.tmp_b - t.tmp_d;
	p->a1 = 2.0 * t.tmp_b * t.tmp_c - t.tmp_e;
	p->a0 = t.tmp_c * t.tmp_c - t.tmp_f;
}

/*
** To calculate the normal coordinates we find the partial derivative of
** the torus equation and find coordinates (𝜕f/𝜕x, 𝜕f/𝜕y, 𝜕f/𝜕z).
*/

void		normal_tore(double normal[4], double p[4], t_obj *s)
{
	double	k;

	k = 4 * (p[0] * p[0] + p[1] * p[1] + p[2] * p[2]
			+ s->r_tore * s->r_tore - s->rayon * s->rayon);
	normal[0] = p[0] * k - 8 * s->r_tore * s->r_tore * p[0];
	normal[1] = p[1] * k;
	normal[2] = p[2] * k - 8 * s->r_tore * s->r_tore * p[2];
	normal[3] = 1;
}

/*
** The inter_torus function checks if their is an intersection between the
** torus and the ray. It returns respectively 0 if their is no intersection,
** a double over 0 if their is an intersection and then find the coordinates of
** this point and the normal coordinates at this point.
*/

double		inter_tore(t_ray r, t_obj *s)
{
	t_polynom	p;
	t_ray		r2;
	double		res;
	double		tmp[4];
	double		tmp2[4];

	inv_transformation(&s->t, r2.ori, r.ori);
	point_matrix(r2.dir, r.dir, s->t.inv_rotation);
	calc_coeff(&p, r2, s);
	resolv(&p);
	res = closest_inter(p);
	if (res == -1)
		return (0);
	cal_point(r2, tmp, res);
	normal_tore(tmp2, tmp, s);
	point_matrix(s->normal2, tmp2, s->t.rotation);
	if (dot_product(r2.dir, tmp2) < 0 && s->reflect == 0.0)
		double_vec(tmp2, -1, tmp2);
	normalize(tmp2);
	transformation(&s->t, s->point, tmp);
	point_matrix(s->normal, tmp2, s->t.rotation);
	normalize(s->normal);
	return (res);
}
