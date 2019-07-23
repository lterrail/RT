/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 18:58:26 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/21 11:35:34 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_data(t_data *data, t_scene *scene)
{
	init_vec(data->color);
	data->depth = scene->param.depth;
	data->hit = NULL;
	data->d = 0;
	init_vec(data->point);
	init_vec(data->norm);
	init_vec(data->diffuse);
	init_vec(data->ambiant);
	init_vec(data->specular);
	data->ir_actual = 1.0;
}

t_all		init_var(t_all all)
{
	if (!(all.mlx.p_mlx = mlx_init()))
		free_scene(MLX_ERROR, &all, NULL);
	if (!(all.mlx.p_win = mlx_new_window(all.mlx.p_mlx, SIZE_W, SIZE_H, "rt")))
		free_scene(MLX_ERROR, &all, NULL);
	if (!(all.mlx.p_img = mlx_new_image(all.mlx.p_mlx, SIZE_W, SIZE_H)))
		free_scene(MLX_ERROR, &all, NULL);
	if (!(all.img.img = mlx_get_data_addr(all.mlx.p_img,
			&(all.img.bits_per_pixel),
			&(all.img.size_line),
			&(all.img.endian))))
		free_scene(MLX_ERROR, &all, NULL);
	all.file = 0;
	return (all);
}

void		init_vec(double vec[4])
{
	int	i;

	i = -1;
	while (++i < 3)
		vec[i] = 0;
	vec[3] = 1;
}

void		init_transform(t_transform *t, double pos[4], double dir[4])
{
	id_matrix(t->transformation);
	id_matrix(t->translation);
	id_matrix(t->rotation);
	id_matrix(t->inv_rotation);
	id_matrix(t->inv_translation);
	id_matrix(t->inv_transformation);
	translation(t, pos);
	rotation(t, dir);
}

void		set_vec(double vec[4], double x, double y, double z)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = z;
}
