/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin_interpolation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 09:36:58 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/05 11:12:54 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	perlin(double x, double y, t_noise *p)
{
	double	tmp;
	double	li;
	double	lj;

	tmp = x - p->x_s;
	p->cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
	li = p->s + p->cx * (p->t - p->s);
	lj = p->u + p->cx * (p->v - p->u);
	tmp = y - p->y_s;
	p->cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
	return (li + p->cy * (lj - li));
}

double	wood(double x, double y, t_noise *p)
{
	double	tmp;
	double	li;
	double	lj;
	double	v;

	tmp = x - p->x_s;
	p->cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
	li = p->s + p->cx * (p->t - p->s);
	lj = p->u + p->cx * (p->v - p->u);
	tmp = y - p->y_s;
	p->cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
	v = 20 * (li + p->cy * (lj - li));
	return (v);
}

double	marble(double x, double y, t_noise *p)
{
	double	tmp;
	double	li;
	double	lj;

	tmp = x - p->x_s;
	p->cx = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
	li = p->s + p->cx * (p->t - p->s);
	lj = p->u + p->cx * (p->v - p->u);
	tmp = y - p->y_s;
	p->cy = 3 * tmp * tmp - 2 * tmp * tmp * tmp;
	return (cos(x + li + p->cy * (lj - li)));
}
