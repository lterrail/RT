/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_mesh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 18:25:33 by lterrail          #+#    #+#             */
/*   Updated: 2019/06/21 11:05:40 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** These functions allow to find the intersection point between a ray
** and a triange and then calcul the coordinates of the normal
** vector at the hit point.
*/

/*
** mesh.v0 && mesh.v1 && mesh.v2 = points of one triangle given in the file .obj
** u && v = vectors of the triangle plane, then we can calculate the normal
** w = vector between one point of the triangle and the origin
** gd = cos(normal, ray direction)
** if fabs(gd) < EPSILON = verify if ray direction isn't parallel with the plane
** a > E && b > E && a + b <= 1.0
** verify if the intersection point is inside the triangle
*/

double		meshsovler(t_obj *obj, t_ray r, double a, double b)
{
	double	u[4];
	double	v[4];
	double	w[4];
	double	gd;
	double	tmp[4];

	sub_vec(obj->mesh.v1, obj->mesh.v0, u);
	sub_vec(obj->mesh.v2, obj->mesh.v0, v);
	sub_vec(r.ori, obj->mesh.v0, w);
	crossproduct(u, v, obj->normal);
	gd = -dot_product(obj->normal, r.dir);
	if (fabs(gd) < E)
		return (-1);
	crossproduct(w, v, tmp);
	a = -dot_product(tmp, r.dir) / gd;
	crossproduct(u, w, tmp);
	b = -dot_product(tmp, r.dir) / gd;
	if (a > E && b > E && a + b <= 1.0)
		return (dot_product(obj->normal, w) / gd);
	return (-1);
}

double		inter_mesh(t_ray r, t_obj *s)
{
	t_ray		r2;
	double		res;
	double		tmp[4];
	double		tmp2[4];

	inv_transformation(&s->t, r2.ori, r.ori);
	point_matrix(r2.dir, r.dir, s->t.inv_rotation);
	res = meshsovler(s, r2, 0.0, 0.0);
	if (res == -1.0)
		return (-1);
	cal_point(r2, tmp, res);
	ft_memcpy(tmp2, s->normal, sizeof(double) * 4);
	if (dot_product(r2.dir, tmp2) < 0 && s->reflect == 0.0)
		double_vec(tmp2, -1, tmp2);
	point_matrix(s->normal2, tmp2, s->t.rotation);
	point_matrix(s->normal, tmp2, s->t.rotation);
	transformation(&s->t, s->point, tmp);
	normalize(s->normal);
	return (res);
}
