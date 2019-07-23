/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter_quadric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 09:53:35 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/13 19:54:22 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** These functions allow to find the intersection point between a ray
** and a quadric and then calcul the coordinates of the normal
** vector at the hit point.
*/

double	inter_quadric(t_ray r, t_obj *s, int flag)
{
	t_ray	r2;
	double	res;
	double	tmp[4];
	double	tmp2[4];

	inv_transformation(&s->t, r2.ori, r.ori);
	point_matrix(r2.dir, r.dir, s->t.inv_rotation);
	res = quadric_solver(s->q, r2);
	if (res <= E)
		return (0);
	cal_point(r2, tmp, res);
	normalquadric(tmp2, tmp, s->q);
	normalize(tmp2);
	point_matrix(s->normal2, tmp2, s->t.rotation);
	if (dot_product(r2.dir, tmp2) < 0)
		double_vec(tmp2, -1, tmp2);
	ft_memcpy(s->normal, tmp2, sizeof(double) * 4);
	if (flag == 1)
		get_texture(s);
	transformation(&s->t, s->point, tmp);
	point_matrix(s->normal, tmp2, s->t.rotation);
	normalize(s->normal);
	return (res);
}
