/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_obj_material.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:35:00 by lterrail          #+#    #+#             */
/*   Updated: 2019/06/27 17:00:53 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		fill_obj_material_3(char *line, t_obj *obj)
{
	if (is_token(line, "type"))
	{
		if (!(obj->e_quadric = get_quadric_type(line)))
			return (E_ERROR);
	}
	else if (is_token(line, "normal"))
	{
		if (!(get_vec(obj->normal, line)))
			return (E_ERROR);
	}
	else if (is_token(line, "texture"))
	{
		if (!(obj->texture.e_text = get_type_text(line)))
			return (E_ERROR);
	}
	else if (is_token(line, "frequency"))
		obj->texture.freq = get_value(line);
	else if (is_token(line, "transparency"))
		obj->transparency = get_value(line);
	else if (is_token(line, "direction"))
	{
		if (!get_vec(obj->dir, line))
			return (E_ERROR);
	}
	return (E_SUCCESS);
}

static int		fill_obj_material_2(char *line, t_obj *obj)
{
	if (is_token(line, "shine"))
		obj->shine = get_value(line);
	if (is_token(line, "ambiant"))
		obj->ambiant = get_value(line);
	else if (is_token(line, "specularity"))
		obj->p_spec = get_value(line);
	else if (is_token(line, "reflection"))
		obj->reflect = get_value(line);
	else if (is_token(line, "refraction"))
		obj->refract = get_value(line);
	else if (is_token(line, "rayon_tore"))
		obj->r_tore = get_value(line);
	else if (is_token(line, "path"))
	{
		if (!(obj->path = ft_strdup(&line[5])))
			return (E_ERROR);
		obj->path[ft_strlen(obj->path) - 1] = 0;
	}
	else
	{
		if (!fill_obj_material_3(line, obj))
			return (E_ERROR);
	}
	return (E_SUCCESS);
}

int				fill_obj_material(char **file, t_obj *obj, int *i)
{
	while (ft_strcmp(file[*i], "}"))
	{
		if (is_token(file[*i], "position"))
		{
			if (!get_vec(obj->pos, file[*i]))
				return (E_ERROR);
		}
		else if (is_token(file[*i], "rayon"))
			obj->rayon = get_value(file[*i]);
		else if (is_token(file[*i], "albedo"))
			obj->albedo = get_value(file[*i]);
		else if (is_token(file[*i], "alpha"))
			obj->alpha = get_value(file[*i]);
		else if (is_token(file[*i], "color"))
		{
			if (!get_color(obj->color, file[*i]))
				return (E_ERROR);
		}
		else if (!fill_obj_material_2(file[*i], obj))
			return (E_ERROR);
		(*i)++;
	}
	return (check_values(obj)) ? E_SUCCESS : E_ERROR;
}
