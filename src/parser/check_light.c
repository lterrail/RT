/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:21:51 by lterrail          #+#    #+#             */
/*   Updated: 2019/06/18 16:16:20 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_light_token(char **file, int i, int flag)
{
	if (flag == 1 && ft_strcmp(file[i], "light"))
		return (-1);
	if (flag == 2 && !is_token(file[i], "position")
			&& !is_token(file[i], "color")
			&& !is_token(file[i], "intensity"))
		return (-2);
	return (E_SUCCESS);
}

static int	check_lux(char **file, int *line)
{
	int	i;

	i = *line;
	if (check_light_token(file, i, 1) == -1)
		return (ERR_LIGHT);
	i += 2;
	while (file[i] && ft_strcmp(file[i], "}"))
	{
		if (check_light_token(file, i, 2) == -2)
			return (ERR_LIGHT);
		if (!check_var(file[i]))
			return (ERR_LIGHT);
		i++;
	}
	if (i == *line + 2)
		return (ERR_LIGHT);
	*line = i;
	return (E_SUCCESS);
}

int			check_lights(char **file, int *line)
{
	int	i;
	int	j;
	int	ret;

	ret = 0;
	i = *line + 1;
	j = count_elem(&(file[i - 1])) + i;
	while (++i < j && ft_strcmp(file[i], "}"))
	{
		if ((ret = check_lux(file, &i)) < 0)
			return (ret);
	}
	*line = i;
	return (E_SUCCESS);
}
