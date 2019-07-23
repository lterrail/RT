/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vector2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 12:58:02 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/12 15:52:54 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	crossproduct(double a[4], double b[4], double vec[4])
{
	vec[3] = 1;
	vec[0] = a[1] * b[2] - a[2] * b[1];
	vec[1] = a[2] * b[0] - a[0] * b[2];
	vec[2] = a[0] * b[1] - a[1] * b[0];
}

double	dot_product(double u[4], double v[4])
{
	int		i;
	double	res;

	res = 0;
	i = -1;
	while (++i < 3)
		res += u[i] * v[i];
	return (res);
}
