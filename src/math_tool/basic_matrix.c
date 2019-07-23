/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 15:37:31 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/12 11:06:37 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transformation.h"

/*
** These functions are designed to do basic operations on matrix[4][4]
** and matrix[4] as vectors of homogeneous coordinates **
*/

/*
** The function point_matrix gets the product between matrix[4][4]
** and matrix[4]. The result is registered in res which is a matrix[4].
*/

extern void	point_matrix(double *res, double p[4], double m[4][4])
{
	int		i;
	int		j;
	double	y;

	i = -1;
	while (++i < 4)
	{
		y = 0.0;
		j = -1;
		while (++j < 4)
			y += m[i][j] * p[j];
		res[i] = y;
	}
	if (res[3] != 0.0)
	{
		i = -1;
		while (++i < 4)
			res[i] /= res[3];
	}
}

/*
** The function mult_matrix gets the product between matrix[4][4]
** and matrix[4][4]. The result is registered in res which is a matrix[4][4].
*/

extern void	mult_matrix(double res[4][4], double m1[4][4], double m2[4][4])
{
	int		i;
	int		j;
	int		k;
	double	m;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			k = -1;
			m = 0;
			while (++k < 4)
				m += m1[i][k] * m2[k][j];
			res[i][j] = m;
		}
	}
}

/*
** The function null_matrix initializes matrix[4][4] with 0
*/

extern void	null_matrix(double m[4][4])
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			m[i][j] = 0;
	}
}

/*
** The function id_matrix initializes identity matrix[4][4]
*/

extern void	id_matrix(double m[4][4])
{
	int	i;

	i = -1;
	null_matrix(m);
	while (++i < 4)
		m[i][i] = 1;
}
