/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 17:56:03 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/13 10:26:14 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRANSFORMATION_H
# define TRANSFORMATION_H
# include <math.h>
# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# define PI 3.141592653589793238462

typedef struct	s_quadric
{
	double		a;
	double		b;
	double		c;
	double		d;
	double		e;
	double		f;
	double		g;
	double		h;
	double		i;
	double		j;
	double		aa;
	double		bb;
	double		cc;
	double		t1;
	double		t2;
	double		t;
}				t_quadric;

typedef struct	s_transform
{
	double		translation[4][4];
	double		rotation[4][4];
	double		scale[4][4];
	double		transformation[4][4];
	double		inv_translation[4][4];
	double		inv_rotation[4][4];
	double		inv_scale[4][4];
	double		inv_transformation[4][4];
}				t_transform;

/*
** trans_matrix2.c
*/

void			convert_rad(double *vec);
void			normalize(double vec[4]);
void			inv_transformation(t_transform *t, double res[4],
				double vec[4]);
void			transformation(t_transform *t, double res[4], double vec[4]);

/*
** trans_matrix.c
*/

void			rotation(t_transform *t, double *rotation);
void			translation(t_transform *t, double *m);
void			scale(t_transform *t, double *scale);

/*
** basic_matrix.c
*/

void			null_matrix(double m[4][4]);
void			id_matrix(double m[4][4]);
void			mult_matrix(double res[4][4], double m1[4][4], double m2[4][4]);
void			point_matrix(double *res, double p[4], double m[4][4]);

#endif
