/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:55:04 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/20 12:39:08 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	fill_cam(char **file, t_scene *scene)
{
	int	i;
	int	ret;

	i = 0;
	while (ft_strcmp(file[i], "camera"))
		i++;
	if ((ret = get_vec(scene->cam.pos, file[i + 2]) < 0))
		return (ret);
	if ((ret = get_vec(scene->cam.dir, file[i + 3]) < 0))
		return (ret);
	return (E_SUCCESS);
}

int			parse(char **file, t_scene *scene)
{
	int	ret;

	ret = 0;
	if ((ret = fill_param(file, scene)) < 0)
		return (ret);
	if ((ret = fill_cam(file, scene)) < 0)
		return (ret);
	if ((ret = fill_obj(file, scene)) < 0)
		return (ret);
	if ((ret = fill_light(file, scene)) < 0)
		return (ret);
	return (E_SUCCESS);
}
