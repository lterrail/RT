/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_param.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/10 16:45:39 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/18 17:37:22 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_param_token(char **file, int i, int flag)
{
	if (flag == 1 && ft_strcmp(file[i], "param"))
		return (-1);
	if (flag == 2 && !is_token(file[i], "shader")
			&& !is_token(file[i], "depth")
			&& !is_token(file[i], "antialiasing")
			&& !is_token(file[i], "blindlight"))
		return (-2);
	return (E_SUCCESS);
}

int			check_param(char **file, int *line)
{
	int	i;
	int	j;

	i = *line;
	j = count_elem(&(file[i]));
	if (j != 6 || ft_strcmp(file[i + 1], "{") || ft_strcmp(file[i + 6], "}"))
		return (ERR_PARAM);
	if (check_param_token(file, i, 1) == -1)
		return (ERR_PARAM);
	i += 2;
	while (file[i] && ft_strcmp(file[i], "}"))
	{
		if (check_param_token(file, i, 2) == -2)
			return (ERR_PARAM);
		if (!check_var(file[i]))
			return (ERR_PARAM);
		i++;
	}
	if (i == *line + 2)
		return (ERR_PARAM);
	*line = i;
	return (E_SUCCESS);
}
