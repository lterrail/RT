/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:38:37 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/10 12:22:12 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Calculation of the direct light
*/

void	direct_light(t_lux *light, t_data *data, t_ray r)
{
	t_lux	*tmp;
	double	color[4];
	double	dirlight[4];
	double	cosi;
	double	dl2;

	tmp = light;
	while (tmp)
	{
		if (tmp->direct == 1)
		{
			double_vec(light->color, 1, color);
			sub_vec(tmp->pos, r.ori, dirlight);
			dl2 = square_norm(dirlight);
			normalize(dirlight);
			cosi = dot_product(dirlight, r.dir);
			cosi = clamp(cosi, 0, 1);
			if (dl2 != 0.0)
				cosi = (light->lux * pow(cosi, 4.0)) / dl2;
			double_vec(color, cosi, data->direct);
			add_vec(data->color, data->direct, data->color);
		}
		tmp = tmp->next;
	}
}

/*
** Checking if we can see directly the light
*/

void	check_direct_light(t_scene *scene)
{
	t_lux	*tmp;
	double	dl2;
	t_ray	r;
	t_data	data;

	tmp = scene->light;
	double_vec(scene->cam.pos, 1, r.ori);
	while (tmp)
	{
		init_data(&data, scene);
		sub_vec(tmp->pos, r.ori, r.dir);
		dl2 = square_norm(r.dir);
		normalize(r.dir);
		closest_obj(scene->obj, r, &data);
		if ((data.hit != NULL && (data.d * data.d) < dl2)
				|| scene->param.light == 0)
			tmp->direct = 0;
		else
			tmp->direct = 1;
		tmp = tmp->next;
	}
}
