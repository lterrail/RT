/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:43:41 by fcottet           #+#    #+#             */
/*   Updated: 2019/07/01 12:30:41 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_obj(t_obj *obj)
{
	init_vec(obj->pos);
	obj->ambiant = 0.2;
	obj->path = 0;
	obj->texture.img = 0;
	obj->texture.i = 0;
	obj->texture.j = 0;
	obj->rayon = 4;
	obj->texture.img = 0;
	obj->albedo = 0.5;
	obj->alpha = 0.5;
	obj->shine = 0.5;
	obj->p_spec = 50;
	obj->reflect = 0;
	obj->transparency = 0;
	obj->refract = 0.99;
	obj->down = NULL;
	obj->r_tore = 2;
	obj->id = 0;
}

static t_obj	*new_obj(char *type)
{
	t_obj	*new;

	if (!(new = malloc(sizeof(t_obj))))
		return (NULL);
	new->next = NULL;
	if (!ft_strcmp(type, "quadric"))
		new->e_type = QUADRIC;
	else if (!ft_strcmp(type, "mesh"))
		new->e_type = MESH;
	else if (!ft_strcmp(type, "tore"))
		new->e_type = TORE;
	else if (!ft_strcmp(type, "cube"))
		new->e_type = CUBE;
	else
		new->e_type = 0;
	return (new);
}

void			add_obj(t_obj **head, t_obj *new)
{
	t_obj	*tmp;

	if (head && new)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int		fill_elem(char **file, t_scene *scene, int *i, int *id)
{
	t_obj	*new;
	int		ret;

	ret = 0;
	if (!(new = new_obj(file[*i])))
		return (ERR_FILL_OBJ);
	init_obj(new);
	if (!fill_obj_material(file, new, i))
	{
		free(new);
		return (ERR_FILL_OBJ);
	}
	if (scene->obj == NULL)
		scene->obj = new;
	else
		add_obj(&(scene->obj), new);
	new->id = *id;
	if (new->e_quadric == SPHERE)
		printf("sphere %f\n", new->reflect);
	else
		printf("plan %f\n", new->reflect);
	if (new->e_type == MESH)
		if ((ret = check_mesh(new, id)) < 0)
			return (ret);
	return (E_SUCCESS);
}

int				fill_obj(char **file, t_scene *scene)
{
	int	i;
	int	j;
	int id;
	int	ret;

	ret = 0;
	i = 0;
	id = 0;
	while (ft_strcmp(file[i], "objects"))
		i++;
	scene->obj = NULL;
	j = count_elem(&(file[i])) + i;
	while (i < j)
	{
		if (!ft_strcmp(file[i], "quadric") || !ft_strcmp(file[i], "mesh")
				|| !ft_strcmp(file[i], "tore") || !ft_strcmp(file[i], "cube"))
		{
			if ((ret = fill_elem(file, scene, &i, &id)) < 0)
				return (ret);
			id++;
		}
		i++;
	}
	return (E_SUCCESS);
}
