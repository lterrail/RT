/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:40:27 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/12 18:45:40 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "transformation.h"

/*
** Initialize the translation of the matrix of transformation and
** inv_transformation witch avoid to calculate the transpose matrix.
*/

void		translation(t_transform *t, double *pos)
{
	double		tmp[4][4];
	int			i;

	i = -1;
	id_matrix(t->translation);
	id_matrix(t->inv_translation);
	while (++i < 3)
		t->translation[i][3] = pos[i];
	ft_memcpy(tmp, t->transformation, 4 * 4 * sizeof(double));
	mult_matrix(t->transformation, tmp, t->translation);
	i = -1;
	while (++i < 3)
		t->inv_translation[i][3] = -pos[i];
	ft_memcpy(tmp, t->inv_transformation, 4 * 4 * sizeof(double));
	mult_matrix(t->inv_transformation, t->inv_translation, tmp);
}

static void	init_rot(double rx[4][4], double ry[4][4],
					double rz[4][4], double *rot)
{
	id_matrix(rx);
	id_matrix(ry);
	id_matrix(rz);
	rx[1][1] = cos(rot[0]);
	rx[2][1] = sin(rot[0]);
	rx[1][2] = -sin(rot[0]);
	rx[2][2] = cos(rot[0]);
	ry[0][0] = cos(rot[1]);
	ry[2][0] = -sin(rot[1]);
	ry[0][2] = sin(rot[1]);
	ry[2][2] = cos(rot[1]);
	rz[0][0] = cos(rot[2]);
	rz[1][0] = sin(rot[2]);
	rz[0][1] = -sin(rot[2]);
	rz[1][1] = cos(rot[2]);
}

static void	init_inv_rot(double rx[4][4], double ry[4][4],
					double rz[4][4], double *rot)
{
	rx[1][1] = cos(-rot[0]);
	rx[2][1] = sin(-rot[0]);
	rx[1][2] = -sin(-rot[0]);
	rx[2][2] = cos(-rot[0]);
	ry[0][0] = cos(-rot[1]);
	ry[2][0] = -sin(-rot[1]);
	ry[0][2] = sin(-rot[1]);
	ry[2][2] = cos(-rot[1]);
	rz[0][0] = cos(-rot[2]);
	rz[1][0] = sin(-rot[2]);
	rz[0][1] = -sin(-rot[2]);
	rz[1][1] = cos(-rot[2]);
}

/*
** Initialize the rotation of the matrix of transformation and
** inv_transformation witch avoid to calculate the transpose matrix.
*/

void		rotation(t_transform *t, double *rot)
{
	double	rx[4][4];
	double	ry[4][4];
	double	rz[4][4];
	double	tmp[4][4];
	double	tmp2[4][4];

	convert_rad(rot);
	init_rot(rx, ry, rz, rot);
	id_matrix(t->rotation);
	mult_matrix(tmp, t->rotation, rz);
	mult_matrix(tmp2, tmp, ry);
	mult_matrix(t->rotation, tmp2, rx);
	ft_memcpy(tmp, t->transformation, 4 * 4 * sizeof(double));
	mult_matrix(t->transformation, tmp, t->rotation);
	init_inv_rot(rx, ry, rz, rot);
	id_matrix(t->inv_rotation);
	mult_matrix(tmp, t->inv_rotation, rx);
	mult_matrix(tmp2, tmp, ry);
	mult_matrix(t->inv_rotation, tmp2, rz);
	ft_memcpy(tmp, t->inv_transformation, 4 * 4 * sizeof(double));
	mult_matrix(t->inv_transformation, t->inv_rotation, tmp);
}

/*
** Initialize the scale of the matrix of transformation and
** inv_transformation witch avoid to calculate the transpose matrix.
*/

void		scale(t_transform *t, double *scale)
{
	double	tmp[4][4];
	int		i;

	i = -1;
	id_matrix(t->scale);
	id_matrix(t->inv_scale);
	while (++i < 3)
		t->scale[i][i] = scale[i];
	ft_memcpy(tmp, t->transformation, 4 * 4 * sizeof(double));
	mult_matrix(t->transformation, tmp, t->scale);
	i = -1;
	while (++i < 3)
		t->inv_scale[i][i] = 1 / scale[i];
	ft_memcpy(tmp, t->inv_transformation, 4 * 4 * sizeof(double));
	mult_matrix(t->inv_transformation, tmp, t->inv_scale);
}
