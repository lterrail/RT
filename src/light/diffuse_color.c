/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffuse_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 10:28:43 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/13 15:47:23 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		diffuse_color(t_lux *light, t_data *data, double dlight2,
				double lp[4])
{
	double	dirlight[4];
	double	color[4];

	data->phong = 0;
	init_vec(data->diffuse);
	sub_vec(data->point, lp, dirlight);
	normalize(dirlight);
	data->phong = dot_product(dirlight, data->norm);
	if (data->phong < 0)
		data->phong = 0;
	else if (data->phong > 1)
		data->phong = 1;
	data->phong = (light->lux * data->phong) / dlight2;
	data->phong *= data->hit->albedo;
	mult_vec(light->color, data->hit->color, color);
	double_vec(color, data->phong, color);
	add_vec(data->diffuse, color, data->diffuse);
}

static void		specular_light(t_data *data, t_lux *light)
{
	double	dirlight[4];
	double	vec[4];
	double	reflect[4];
	double	i;

	sub_vec(data->point, light->pos, dirlight);
	normalize(dirlight);
	double_vec(data->norm, 2 * dot_product(data->norm, dirlight), vec);
	sub_vec(data->point, light->pos, dirlight);
	sub_vec(dirlight, vec, reflect);
	normalize(reflect);
	normalize(vec);
	i = data->hit->shine * pow(dot_product(reflect, vec), data->hit->p_spec);
	clamp(i, 0, 1);
	double_vec(light->color, i, data->specular);
}

void			add_diff_spec(t_lux *light, t_data *data, double dl2)
{
	diffuse_color(light, data, dl2, light->pos);
	add_vec(data->color, data->diffuse, data->color);
	if (data->inter == 0)
	{
		specular_light(data, light);
		add_vec(data->color, data->specular, data->color);
	}
}
