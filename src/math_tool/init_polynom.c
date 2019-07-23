/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_polynom.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:45:18 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/13 10:33:59 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_polynom(t_polynom *eq)
{
	eq->a0 = 0;
	eq->a1 = 0;
	eq->a2 = 0;
	eq->a3 = 0;
	eq->a4 = 0;
	eq->s1 = DBL_MAX;
	eq->s2 = DBL_MAX;
	eq->s3 = DBL_MAX;
	eq->s4 = DBL_MAX;
	eq->aa2 = 0;
	eq->i = 0;
	eq->d = 0;
	eq->p = 0;
	eq->q = 0;
	eq->r = 0;
	eq->s = 0;
	eq->t = 0;
	eq->q1 = 0;
	eq->q2 = 0;
	eq->q3 = 0;
	eq->r2 = 0;
	eq->s_q = 0;
	eq->an = 0;
	eq->alpha = 0;
}
