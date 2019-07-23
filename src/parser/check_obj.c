/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:52:38 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/18 15:56:59 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_material(char *line)
{
	if (is_token(line, "reflection")
			|| is_token(line, "refraction")
			|| is_token(line, "rayon_tore")
			|| is_token(line, "type")
			|| is_token(line, "path")
			|| is_token(line, "texture")
			|| is_token(line, "frequency")
			|| is_token(line, "ambiant")
			|| is_token(line, "transparency"))
		return (E_SUCCESS);
	return (E_ERROR);
}

static int	check_obj_token(char **file, int i, int flag)
{
	if (flag == 1 && ft_strcmp(file[i], "quadric") && ft_strcmp(file[i], "mesh")
			&& ft_strcmp(file[i], "tore") && ft_strcmp(file[i], "cube"))
		return (WRONG_ELEM_NAME);
	if (flag == 2 && !is_token(file[i], "position")
			&& !is_token(file[i], "rayon")
			&& !is_token(file[i], "albedo")
			&& !is_token(file[i], "height")
			&& !is_token(file[i], "alpha")
			&& !is_token(file[i], "color")
			&& !is_token(file[i], "direction")
			&& !is_token(file[i], "shine")
			&& !is_token(file[i], "path")
			&& !is_token(file[i], "normal")
			&& !is_token(file[i], "specularity") && !is_material(file[i]))
		return (WRONG_MATERIAL_NAME);
	return (E_SUCCESS);
}

static int	check_elem(char **file, int *line)
{
	int	i;

	i = *line;
	if (check_obj_token(file, i, 1) == WRONG_ELEM_NAME)
		return (WRONG_ELEM_NAME);
	i += 2;
	while (file[i] && ft_strcmp(file[i], "}"))
	{
		if (check_obj_token(file, i, 2) == WRONG_MATERIAL_NAME)
			return (WRONG_MATERIAL_NAME);
		if (!check_var(file[i]))
			return (ERR_OBJ);
		i++;
	}
	if (i == *line + 2)
		return (ERR_OBJ);
	*line = i;
	return (E_SUCCESS);
}

int			check_obj(char **file, int *line)
{
	int	j;
	int	i;
	int	ret;

	ret = 0;
	i = *line + 1;
	j = count_elem(&(file[i - 1]));
	while (++i < *line + j)
	{
		if ((ret = check_elem(file, &i)) < 0)
			return (ret);
	}
	*line = i;
	return (E_SUCCESS);
}
