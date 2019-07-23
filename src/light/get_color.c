/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:30:05 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/13 15:47:45 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	parse_inter(t_obj *obj, t_ray r)
{
	double	ret;

	ret = 0.0;
	if (obj->e_type == MESH)
		ret = inter_mesh(r, obj);
	else if (obj->e_type == QUADRIC)
		ret = inter_quadric(r, obj, 0);
	else if (obj->e_type == TORE)
		ret = inter_tore(r, obj);
	else if (obj->e_type == CUBE)
		ret = inter_cube(r, obj);
	return (ret);
}

static void		closestshadow(t_obj *tmp, t_ray r, t_data *data, t_shadow *dobj)
{
	double	ret;
	double	res[4];

	ret = parse_inter(tmp, r);
	if (ret > 0.0)
	{
		sub_vec(tmp->point, r.ori, res);
		ret = square_norm(res);
	}
	if (ret > 0.0 && (ret < dobj->d || dobj->d == 0)
		&& tmp->id != data->hit->id)
	{
		dobj->hit = tmp;
		dobj->d = ret;
	}
	if (ret > 0.0 && ret < dobj->dl2)
	{
		data->inter = 1;
		if (tmp->transparency == 1)
			mult_vec(dobj->color, tmp->color, dobj->color);
		else
			init_vec(dobj->color);
	}
}

static t_shadow	is_valid_shadow(t_obj *obj, t_ray r,
		t_data *data, t_shadow dobj)
{
	t_obj		*tmp;
	t_obj		*tmp2;

	tmp = obj;
	data->inter = 0;
	dobj.d = 0;
	dobj.hit = NULL;
	double_vec(data->hit->color, 0.2, dobj.color);
	while (tmp)
	{
		if (tmp->e_type == MESH)
		{
			tmp2 = tmp->down;
			while (tmp2)
			{
				closestshadow(tmp2, r, data, &dobj);
				tmp2 = tmp2->next;
			}
		}
		else if (tmp->e_type != MESH)
			closestshadow(tmp, r, data, &dobj);
		tmp = tmp->next;
	}
	return (dobj);
}

static t_shadow	check_shadow(t_obj *obj, t_lux *light, t_data *data,
		t_shadow dobj)
{
	t_ray		shadow;

	double_vec(data->norm, E, shadow.ori);
	add_vec(shadow.ori, data->point, shadow.ori);
	sub_vec(light->pos, shadow.ori, shadow.dir);
	dobj = is_valid_shadow(obj, shadow, data, dobj);
	return (dobj);
}

void			getcolor(t_scene *scene, t_data *data)
{
	t_lux		*tmp;
	double		l[4];
	t_shadow	dobj;

	double_vec(data->hit->point, 1, data->point);
	double_vec(data->hit->normal, 1, data->norm);
	tmp = scene->light;
	while (tmp)
	{
		sub_vec(data->point, tmp->pos, l);
		dobj.dl2 = square_norm(l);
		dobj = check_shadow(scene->obj, tmp, data, dobj);
		if (dobj.hit != NULL && dobj.d < dobj.dl2
				&& data->hit->texture.e_text != SKYBOX)
			add_vec(data->color, dobj.color, data->color);
		else
			add_diff_spec(tmp, data, dobj.dl2);
		tmp = tmp->next;
	}
	double_vec(data->hit->color, data->hit->ambiant, data->ambiant);
	add_vec(data->color, data->ambiant, data->color);
}
