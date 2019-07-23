/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_obj.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 10:10:53 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/13 15:42:53 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	is_valid(t_ray r, t_obj *obj, double *d)
{
	double	ret;

	ret = 0;
	if (obj->e_type == QUADRIC && ((ret = inter_quadric(r, obj, 1)) > 0)
		&& (ret < *d || *d == 0))
		*d = ret;
	else if (obj->e_type == TORE && ((ret = inter_tore(r, obj)) > 0
				&& (ret < *d || *d == 0)))
		*d = ret;
	else if (obj->e_type == CUBE && ((ret = inter_cube(r, obj)) > 0
				&& (ret < *d || *d == 0)))
		*d = ret;
	else if (obj->e_type == MESH && ((ret = inter_mesh(r, obj)) > 0
				&& (ret < *d || *d == 0)))
		*d = ret;
	else
		return (0);
	return (1);
}

static void		closest_mesh(t_obj *tmp, t_ray r, t_data *data, double *d)
{
	t_obj	*tmp2;
	int		ret;

	tmp2 = tmp->down;
	while (tmp2)
	{
		ret = is_valid(r, tmp2, d);
		if (ret > 0)
			data->hit = tmp2;
		tmp2 = tmp2->next;
	}
}

void			closest_obj(t_obj *obj, t_ray r, t_data *data)
{
	t_obj	*tmp;
	int		ret;
	double	d;

	d = 0;
	tmp = obj;
	data->hit = NULL;
	while (tmp)
	{
		if (tmp->e_type == MESH)
			closest_mesh(tmp, r, data, &d);
		if (tmp->e_type != MESH)
		{
			ret = is_valid(r, tmp, &d);
			if (ret > 0)
				data->hit = tmp;
		}
		tmp = tmp->next;
	}
	if (data->hit != NULL)
		data->d = d;
}
