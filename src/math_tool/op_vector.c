/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/12 13:51:26 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/12 15:11:06 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Define basic opreration on vectors : addition, multiplication,
** substraction. square_norm return the square norm of the vector passed
** in parameter. We always use the square norm for optimisation and do not
** call the sqrt function for each operation.
*/

void	add_vec(double a[4], double b[4], double c[4])
{
	c[3] = 1;
	c[0] = a[0] + b[0];
	c[1] = a[1] + b[1];
	c[2] = a[2] + b[2];
}

void	double_vec(double a[4], double b, double c[4])
{
	c[3] = 1;
	c[0] = a[0] * b;
	c[1] = a[1] * b;
	c[2] = a[2] * b;
}

void	sub_vec(double a[4], double b[4], double c[4])
{
	c[3] = 1;
	c[0] = a[0] - b[0];
	c[1] = a[1] - b[1];
	c[2] = a[2] - b[2];
}

void	mult_vec(double a[4], double b[4], double c[4])
{
	c[3] = 1;
	c[0] = a[0] * b[0];
	c[1] = a[1] * b[1];
	c[2] = a[2] * b[2];
}

double	square_norm(double a[4])
{
	double	result;

	a[3] = 1;
	result = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	return (result);
}
