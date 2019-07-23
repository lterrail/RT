/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 16:25:49 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/12 12:54:01 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** Calculation of the reflected ray;
*/

t_ray	reflection(t_ray r, t_data *data)
{
	t_ray	new;

	double_vec(data->hit->normal2, 2 * dot_product(data->hit->normal2,
				r.dir), new.dir);
	sub_vec(r.dir, new.dir, new.dir);
	normalize(new.dir);
	double_vec(data->hit->normal2, E, new.ori);
	add_vec(data->hit->point, new.ori, new.ori);
	return (new);
}
