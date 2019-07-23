/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:58:09 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/21 11:37:16 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	quit_all(t_all *all)
{
	mlx_destroy_image(all->mlx.p_mlx, all->mlx.p_img);
	mlx_destroy_window(all->mlx.p_mlx, all->mlx.p_win);
	exit(0);
}
