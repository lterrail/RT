/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:00:31 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/19 18:20:34 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_quadric	init_quad(double b, double c, double j, double h)
{
	t_quadric	q;

	init_quadric(&q);
	q.a = 1;
	q.b = b;
	q.c = c;
	q.j = j;
	q.h = h;
	return (q);
}

static t_quadric	init_plan(double g, double h, double i, double j)
{
	t_quadric	q;

	init_quadric(&q);
	q.g = g;
	q.h = h;
	q.i = i;
	q.j = j;
	return (q);
}

static void			load_quadric2(t_quadric *q, t_obj *obj, double b, double c)
{
	if (obj->e_quadric == 8)
		*q = init_quad(0, -c, -obj->rayon * obj->rayon, 0);
	else if (obj->e_quadric == 9)
	{
		*q = init_quad(0, 0, 0, 0);
		q->i = 2;
	}
	else if (obj->e_quadric == 10)
		*q = init_quad(b, 1, -obj->rayon * obj->rayon, 0);
	else if (obj->e_quadric == 11)
		*q = init_quad(1, 1, -obj->rayon * obj->rayon, 0);
	else if (obj->e_quadric == 12)
		*q = init_quad(0, 1, 0, -1);
	else if (obj->e_quadric == 13)
		*q = init_quad(-b, 1, -obj->rayon * obj->rayon, 0);
	else if (obj->e_quadric == 14)
		*q = init_quad(-b, 1, obj->rayon * obj->rayon, 0);
	else if (obj->e_quadric == 15)
		*q = init_quad(-b, 1, 0, 0);
	else if (obj->e_quadric == 16)
		*q = init_quad(0, 1, -obj->rayon * obj->rayon, 0);
	else if (obj->e_quadric == 17)
		*q = init_plan(obj->normal[0], obj->normal[1], obj->normal[2], 0);
}

static void			load_quadric(t_quadric *q, t_obj *obj)
{
	double	b;
	double	c;
	double	r;

	b = obj->alpha;
	c = obj->alpha + 3;
	r = obj->rayon * obj->rayon;
	if (obj->e_quadric == 1)
		*q = init_quad(b, c, -r, 0);
	else if (obj->e_quadric == 2)
		*q = init_quad(0, b, 0, -1);
	else if (obj->e_quadric == 3)
		*q = init_quad(0, -b, 0, -1);
	else if (obj->e_quadric == 4)
		*q = init_quad(-b, c, -r, 0);
	else if (obj->e_quadric == 5)
		*q = init_quad(-b, c, r, 0);
	else if (obj->e_quadric == 6)
		*q = init_quad(b, -c, 0, 0);
	else if (obj->e_quadric == 7)
		*q = init_quad(0, c, -r, 0);
	else
		load_quadric2(q, obj, b, c);
}

int					load_obj(t_obj *obj)
{
	t_obj	*tmp;
	int		ret;

	tmp = obj;
	ret = 0;
	while (tmp)
	{
		if (tmp->texture.e_text == SKYBOX && tmp->e_quadric == SPHERE)
			init_skybox(tmp);
		if ((tmp->texture.e_text == BMP || tmp->texture.e_text == SKYBOX)
			&& tmp->e_quadric == SPHERE)
		{
			if ((ret = load_img(tmp->path, &tmp->texture)) < 0)
				return (ret);
		}
		else if ((tmp->texture.e_text == PERLIN || tmp->texture.e_text == WOOD
					|| tmp->texture.e_text == MARBLE)
					&& tmp->e_quadric == SPHERE)
			if ((ret = init_perlin(tmp)) < 0)
				return (ret);
		init_transform(&tmp->t, tmp->pos, tmp->dir);
		load_quadric(&tmp->q, tmp);
		tmp = tmp->next;
	}
	return (EXIT_SUCCESS);
}
