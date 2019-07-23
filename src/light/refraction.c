/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refraction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 16:41:46 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/13 15:47:59 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	fresnel(t_ref ref)
{
	double	sint;
	double	cost;
	double	rs;
	double	rp;

	sint = ref.etai / ref.etat * sqrtf(get_max(0, (1 - ref.cosi * ref.cosi)));
	cost = sqrtf(get_max(0, 1 - sint * sint));
	ref.cosi = fabs(ref.cosi);
	rs = ((ref.etat * ref.cosi) - (ref.etai * cost))
		/ ((ref.etat * ref.cosi) + (ref.etai * cost));
	rp = ((ref.etai * ref.cosi) - (ref.etat * cost))
		/ ((ref.etai * ref.cosi) + (ref.etat * cost));
	return ((rs * rs + rp * rp) / 2);
}

t_ref	get_ref(t_ray r, t_data *data)
{
	t_ref	ref;

	ft_memcpy(ref.n, data->hit->normal2, sizeof(double) * 4);
	normalize(ref.n);
	ft_memcpy(ref.i, r.dir, sizeof(double) * 4);
	ref.cosi = dot_product(ref.n, ref.i);
	clamp(ref.cosi, -1, 1);
	ref.etai = 1;
	ref.etat = data->hit->refract;
	if (ref.cosi < 0)
		ref.cosi = -ref.cosi;
	else
	{
		double_vec(ref.n, -1, ref.n);
		double_swap(&ref.etai, &ref.etat);
	}
	ref.eta = ref.etai / ref.etat;
	ref.k = 1 - ref.eta * ref.eta * (1 - ref.cosi * ref.cosi);
	return (ref);
}

int		refraction(t_ray r, t_data *data, t_ray *new)
{
	t_ref	ref;

	ref = get_ref(r, data);
	if (ref.k < 0)
		return (0);
	else
	{
		double_vec(ref.i, ref.eta, new->ori);
		double_vec(ref.n, ref.eta * ref.cosi - sqrtf(ref.k), new->dir);
		add_vec(new->ori, new->dir, new->dir);
		double_vec(new->dir, E, new->ori);
		add_vec(data->hit->point, new->ori, new->ori);
		data->kr = fresnel(ref);
	}
	return (1);
}
