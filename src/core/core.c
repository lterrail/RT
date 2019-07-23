/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 11:23:13 by fcottet           #+#    #+#             */
/*   Updated: 2019/07/01 11:46:08 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_rayon(double x, double y, t_cam cam, t_ray *ray)
{
	t_ray		r2;

	cam.dir[3] = 1;
	cam.pos[3] = 1;
	init_transform(&cam.t, cam.pos, cam.dir);
	ft_memcpy(r2.ori, cam.pos, sizeof(double) * 4);
	r2.ori[3] = 1;
	r2.dir[3] = 1;
	r2.dir[0] = x - SIZE_W / 2;
	r2.dir[1] = y - SIZE_H / 2;
	r2.dir[2] = -SIZE_W / (2 * tan((60 * PI / 180) / 2));
	inv_transformation(&cam.t, ray->dir, r2.dir);
	double_vec(r2.ori, 1, ray->ori);
	normalize(ray->dir);
}

static void		anti_aliasing(double ij[2], t_scene *scene, double color[4])
{
	t_aliasing		aa;
	double			tmp[4];
	t_ray			r;
	t_data			data;

	aa.sy = ij[0];
	aa.aa = 1.0 / scene->param.aliasing;
	init_vec(color);
	while (aa.sy < ij[0] + 1.0)
	{
		aa.sx = ij[1];
		while (aa.sx < ij[1] + 1.0)
		{
			init_rayon(aa.sx, aa.sy, scene->cam, &r);
			init_data(&data, scene);
			raytrace(scene, r, &data, scene->param.depth);
			direct_light(scene->light, &data, r);
			double_vec(data.color, (1.0 / pow(scene->param.aliasing,
					2.0)), tmp);
			add_vec(color, tmp, color);
			aa.sx += aa.aa;
		}
		aa.sy += aa.aa;
	}
	double_vec(color, 255, color);
}

static void		*new_thread(void *all)
{
	t_bar		bar;
	double		color[4];
	t_scene		scene;
	int			ret;

	init_bar(&bar, (t_all *)all);
	if ((ret = parse(((t_all *)all)->file, &scene)) < 0)
		free_scene(ret, (t_all *)all, &scene);
	ft_strcpy(((t_all *)all)->shader, scene.param.shader);
	if ((ret = load_obj(scene.obj)) < 0)
		free_scene(ret, (t_all *)all, &scene);
	pthread_mutex_unlock(&((t_all *)all)->mutex);
	check_direct_light(&scene);
	while (bar.ij[0]++ < bar.max)
	{
		bar.ij[1] = -1;
		while (++bar.ij[1] < SIZE_W)
		{
			manage_bar(bar);
			anti_aliasing(bar.ij, &scene, color);
			light_pixel(bar.ij[1], bar.ij[0], &((t_all *)all)->img, color);
		}
	}
	free_scene(ret, all, &scene);
	return (NULL);
}

void			core(t_all *all)
{
	int			k;
	int			ret;
	pthread_t	thread[4];

	all->i = 0;
	if ((ret = read_file(all->av, all)) < 0)
		free_scene(ret, all, NULL);
	pthread_mutex_init(&all->mutex, NULL);
	k = -1;
	while (++k < 4)
	{
		pthread_mutex_lock(&all->mutex);
		if (pthread_create(&thread[k], NULL, new_thread, all) != 0)
			free_scene(ERR_CREATE_THREAD, all, NULL);
	}
	k = -1;
	while (++k < 4)
		pthread_join(thread[k], NULL);
	apply_shader(&all->img, all->shader);
	mlx_put_image_to_window(all->mlx.p_mlx,
			all->mlx.p_win, all->mlx.p_img, 0, 0);
	if (all->file)
		free_tab(all->file);
}
