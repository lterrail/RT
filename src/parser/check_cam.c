/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 16:00:06 by lterrail          #+#    #+#             */
/*   Updated: 2019/06/18 16:00:26 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_cam(char **file, int *line)
{
	int	j;
	int	i;

	i = *line;
	j = count_elem(&(file[i]));
	if (j != 4 || ft_strcmp(file[i + 1], "{") || ft_strcmp(file[i + 4], "}"))
		return (ERR_CAMERA);
	if (!is_token(file[i + 2], "position"))
		return (ERR_CAMERA);
	if (!check_var(file[i + 2]))
		return (ERR_CAMERA);
	if (!is_token(file[i + 3], "direction"))
		return (ERR_CAMERA);
	*line += 4;
	return (E_SUCCESS);
}
