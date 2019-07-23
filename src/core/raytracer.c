/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 16:12:30 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/13 16:51:51 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	recursive_reflection(t_scene *scene, t_ray r,
			t_data *data, double depth)
{
	t_data			tmp;

	getcolor(scene, data);
	depth--;
	tmp = *data;
	init_vec(tmp.color);
	raytrace(scene, reflection(r, &tmp), &tmp, depth);
	clamp_color(tmp.color, 0, 1);
	double_vec(tmp.color, data->hit->reflect, tmp.color);
	double_vec(data->color, 1.0 - data->hit->reflect, data->color);
	add_vec(tmp.color, data->color, data->color);
}

static void	recursive_refraction(t_scene *scene, t_ray r,
			t_data *data, double depth)
{
	double		color[4];
	t_data		tmp;
	t_ray		new;
	double		kr;

	double_vec(data->hit->color, 1, color);
	depth--;
	tmp = *data;
	if ((refraction(r, &tmp, &new) == 1))
	{
		kr = tmp.kr;
		raytrace(scene, new, &tmp, depth);
		mult_vec(data->hit->color, tmp.color, tmp.color);
		double_vec(tmp.color, 1 - kr, tmp.color);
		add_vec(tmp.color, data->color, data->color);
	}
	else
		kr = 1;
	tmp = *data;
	raytrace(scene, reflection(r, &tmp), &tmp, depth);
	double_vec(tmp.color, kr, tmp.color);
	add_vec(tmp.color, data->color, data->color);
}

void		raytrace(t_scene *scene, t_ray r, t_data *data, double depth)
{
	closest_obj(scene->obj, r, data);
	if (data->hit != NULL)
	{
		if (depth == 0 || (data->hit->transparency == 0
			&& data->hit->reflect == 0))
			getcolor(scene, data);
		else if (data->hit->reflect > 0)
			recursive_reflection(scene, r, data, depth);
		else if (data->hit->transparency == 1)
			recursive_refraction(scene, r, data, depth);
	}
}
