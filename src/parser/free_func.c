/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:37:08 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/29 12:36:44 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab || !(*tab))
		return ;
	while (tab[i])
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

static void	free_obj(t_obj **obj)
{
	t_obj	*tmp;

	if (obj)
	{
		while ((*obj))
		{
			tmp = *obj;
			*obj = (*obj)->next;
			if (tmp->path)
				free(tmp->path);
			if (tmp->texture.img)
				free(tmp->texture.img);
			free(tmp);
		}
	}
}

static void	free_mesh(t_obj **obj)
{
	t_obj	*tmp;

	tmp = *obj;
	if (obj)
	{
		while (tmp)
		{
			if (tmp->e_type == MESH)
				free_obj(&(tmp->down));
			tmp = tmp->next;
		}
	}
}

void		free_light(t_lux **light)
{
	t_lux	*tmp;

	if (light)
	{
		while ((*light))
		{
			tmp = *light;
			*light = (*light)->next;
			free(tmp);
		}
	}
}

extern t_err g_errs[];

void		free_scene(int error, t_all *all, t_scene *scene)
{
	if (scene)
	{
		free_mesh(&(scene->obj));
		if (scene->param.shader)
			free(scene->param.shader);
		free_obj(&(scene->obj));
		free_light(&(scene->light));
		scene = NULL;
	}
	if (error < 0)
	{
		ft_putstr_fd(g_errs[-error - 10].name, 2);
		if (all->file)
			free_tab(all->file);
		if (all->mlx.p_mlx)
		{
			if (all->mlx.p_win)
				mlx_destroy_window(all->mlx.p_mlx, all->mlx.p_win);
			if (all->mlx.p_img)
				mlx_destroy_image(all->mlx.p_mlx, all->mlx.p_img);
		}
		exit(0);
	}
}
