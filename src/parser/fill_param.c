/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 17:16:41 by lterrail          #+#    #+#             */
/*   Updated: 2019/06/18 16:57:23 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		fill_param(char **file, t_scene *scene)
{
	int	i;

	i = 0;
	while (file[i] && ft_strcmp(file[i], "param"))
		i++;
	while (file[i] && ft_strcmp(file[i], "}"))
	{
		if (is_token(file[i], "shader"))
		{
			if (!(scene->param.shader = ft_strdup(&file[i][7])))
				return (ERR_FILL_PARAM);
			scene->param.shader[ft_strlen(scene->param.shader) - 1] = '\0';
		}
		else if (is_token(file[i], "blindlight"))
			scene->param.light = get_value(file[i]);
		else if (is_token(file[i], "antialiasing"))
			scene->param.aliasing = get_value(file[i]);
		else if (is_token(file[i], "depth"))
			scene->param.depth = get_value(file[i]);
		i++;
	}
	return (E_SUCCESS);
}
