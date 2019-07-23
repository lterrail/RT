/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_matrix2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:41:27 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/12 13:07:05 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"

void	transformation(t_transform *t, double res[4], double vec[4])
{
	int	i;

	i = -1;
	point_matrix(res, vec, t->transformation);
	if (res[3] != 0.0)
		while (++i < 4)
			res[i] /= res[3];
}

void	inv_transformation(t_transform *t, double res[4], double vec[4])
{
	int	i;

	i = -1;
	point_matrix(res, vec, t->inv_transformation);
	if (res[3] != 0.0)
		while (++i < 4)
			res[i] /= res[3];
}

void	normalize(double *p)
{
	double	d;
	int		i;

	i = -1;
	d = 0;
	while (++i < 3)
		d += p[i] * p[i];
	d = sqrt(d);
	i = -1;
	if (d)
	{
		while (++i < 3)
			p[i] /= d;
	}
}

void	convert_rad(double *rot)
{
	rot[0] = (rot[0] * PI) / 180.0;
	rot[1] = (rot[1] * PI) / 180.0;
	rot[2] = (rot[2] * PI) / 180.0;
}
