/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 17:25:21 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/12 12:19:10 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The functions clamp and clamp_color check if the value
** range between min and max and return respectivly the original value
** if the value is in range, min if the value is less than min,
** max if the value is greater than max.
*/

double	clamp(double a, double min, double max)
{
	if (a < min)
		return (min);
	if (a > max)
		return (max);
	return (a);
}

void	clamp_color(double color[4], double min, double max)
{
	clamp(color[0], min, max);
	clamp(color[1], min, max);
	clamp(color[2], min, max);
}
