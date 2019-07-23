/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:39:26 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/18 16:04:43 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	return_scene_error(int count[7])
{
	if (count[0] > 1)
		return (ERR_TOO_MANY_SCENE);
	else if (count[0] == 0)
		return (ERR_NO_SCENE);
	else if (count[1] > 1)
		return (ERR_TOO_MANY_CAMERA);
	else if (count[1] == 0)
		return (ERR_NO_CAMERA);
	else if (count[2] > 1)
		return (ERR_TOO_MANY_OBJECTS);
	else if (count[2] == 0)
		return (ERR_NO_OBJECTS);
	else if (count[3] == 0)
		return (ERR_NO_ELEM);
	else if (count[4] > 1)
		return (ERR_TOO_MANY_LIGHTS);
	else if (count[4] == 0)
		return (ERR_NO_LIGHTS);
	else if (count[5] == 0)
		return (ERR_NO_LIGTH);
	else if (count[6] > 1)
		return (ERR_TOO_MANY_PARAM);
	else if (count[6] == 0)
		return (ERR_NO_PARAM);
	return (E_SUCCESS);
}

static int	is_valid_scene(char **file)
{
	int	i;
	int	count[7];

	i = -1;
	ft_bzero(count, 7 * sizeof(int));
	while (file[++i])
	{
		if (!ft_strcmp(file[i], "scene"))
			count[0]++;
		if (!ft_strcmp(file[i], "camera"))
			count[1]++;
		else if (!ft_strcmp(file[i], "objects"))
			count[2]++;
		else if (!ft_strcmp(file[i], "quadric") || !ft_strcmp(file[i], "mesh")
				|| !ft_strcmp(file[i], "cube") || !ft_strcmp(file[i], "tore"))
			count[3] = 1;
		else if (!ft_strcmp(file[i], "lights"))
			count[4]++;
		else if (!ft_strcmp(file[i], "light"))
			count[5] = 1;
		else if (!ft_strcmp(file[i], "param"))
			count[6]++;
	}
	return (return_scene_error(count));
}

int			check_semicolon(char *line)
{
	if (!line)
		return (E_ERROR);
	if (line[ft_strlen(line) - 1] != ';')
		return (E_ERROR);
	return (E_SUCCESS);
}

int			check_scene(char **file)
{
	int i;
	int j;
	int ret;

	i = 2;
	ret = 42;
	if ((j = count_elem(file)) != count_line(file) - 1)
		return (WRONG_EMBRACE);
	if ((ret = is_valid_scene(file)) < 0)
		return (ret);
	while (file[i] && i < j && ret > 0)
	{
		if (!ft_strcmp(file[i], "camera"))
			ret = check_cam(file, &i);
		else if (!ft_strcmp(file[i], "objects"))
			ret = check_obj(file, &i);
		else if (!ft_strcmp(file[i], "lights"))
			ret = check_lights(file, &i);
		else if (!ft_strcmp(file[i], "param"))
			ret = check_param(file, &i);
		else if (ft_strcmp(file[i], "}"))
			return (WRONG_EMBRACE);
		i++;
	}
	return (ret > 0 && i != 2) ? 1 : ret;
}
