/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dbl_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 09:44:43 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/12 12:30:28 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The double_swap swap the value contained in a and b.
*/

void	double_swap(double *a, double *b)
{
	double	tmp;

	if (a && b)
	{
		tmp = *a;
		*a = *b;
		*b = tmp;
	}
}
