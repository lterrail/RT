/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:39:30 by lterrail          #+#    #+#             */
/*   Updated: 2019/06/18 18:44:27 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			get_quadric_type_3(char *q)
{
	if (!ft_strcmp(q, "plan"))
		return (17);
	else
		return (E_ERROR);
}

static int	get_quadric_type_2(char *q)
{
	if (!ft_strcmp(q, "elliptic_cone"))
		return (6);
	else if (!ft_strcmp(q, "elliptic_cylinder"))
		return (7);
	else if (!ft_strcmp(q, "hyperbolic_cylinder"))
		return (8);
	else if (!ft_strcmp(q, "parabolic_cylinder"))
		return (9);
	else if (!ft_strcmp(q, "spheroid"))
		return (10);
	else if (!ft_strcmp(q, "sphere"))
		return (11);
	else if (!ft_strcmp(q, "paraboloid"))
		return (12);
	else if (!ft_strcmp(q, "hyperboloid_one"))
		return (13);
	else if (!ft_strcmp(q, "hyperboloid_two"))
		return (14);
	else if (!ft_strcmp(q, "cone"))
		return (15);
	else if (!ft_strcmp(q, "cylinder"))
		return (16);
	return (get_quadric_type_3(q));
}

int			get_quadric_type(char *q)
{
	char	tmp[50];
	int		i;

	i = 0;
	ft_bzero(tmp, 50 * sizeof(char));
	while (*q && *q != ':')
		q++;
	if (*q)
		q++;
	while (*q && *q != ';')
	{
		tmp[i++] = *q;
		q++;
	}
	if (!ft_strcmp(tmp, "ellipsoid"))
		return (1);
	else if (!ft_strcmp(tmp, "elliptic_paraboloid"))
		return (2);
	else if (!ft_strcmp(tmp, "hyperbolic_paraboloid"))
		return (3);
	else if (!ft_strcmp(tmp, "elliptic_hyperboloid_one"))
		return (4);
	else if (!ft_strcmp(tmp, "elliptic_hyperboloid_two"))
		return (5);
	return (get_quadric_type_2(tmp));
}

int			get_type_text(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] != ':')
		i++;
	if (!line[i + 1])
		return (E_ERROR);
	if (!ft_strncmp("bmp;", line + i + 1, ft_strlen(&line[i + 1])))
		return (1);
	else if (!ft_strncmp("perlin;", line + i + 1, ft_strlen(&line[i + 1])))
		return (2);
	else if (!ft_strncmp("wood;", line + i + 1, ft_strlen(&line[i + 1])))
		return (3);
	else if (!ft_strncmp("marble;", line + i + 1, ft_strlen(&line[i + 1])))
		return (4);
	else if (!ft_strncmp("skybox;", line + i + 1, ft_strlen(&line[i + 1])))
		return (5);
	return (E_ERROR);
}
