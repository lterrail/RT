/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:55:20 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/25 18:32:03 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_lux	*new_light(void)
{
	t_lux	*new;

	if (!(new = malloc(sizeof(t_lux))))
		return (NULL);
	new->next = NULL;
	init_vec(new->color);
	init_vec(new->inter);
	init_vec(new->pos);
	init_vec(new->normal);
	new->lux = 0;
	return (new);
}

static void		add_light(t_lux **head, t_lux *new)
{
	t_lux	*tmp;

	if (head && new)
	{
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

static int		get_lux(char **file, t_lux *light, int *i)
{
	while (ft_strcmp(file[*i], "}"))
	{
		if (is_token(file[*i], "position"))
		{
			if (!get_vec(light->pos, file[*i]))
				return (E_ERROR);
		}
		else if (is_token(file[*i], "intensity"))
			light->lux = get_value(file[*i]);
		else if (is_token(file[*i], "color"))
			if (!get_color(light->color, file[*i]))
				return (E_ERROR);
		(*i)++;
	}
	return (E_SUCCESS);
}

static int		fill_lux(char **file, t_scene *scene, int *i)
{
	t_lux	*new;

	if (!(new = new_light()))
		return (ERR_FILL_LIGHT);
	if (!get_lux(file, new, i))
	{
		free(new);
		return (ERR_FILL_LIGHT);
	}
	if (scene->light == NULL)
		scene->light = new;
	else
		add_light(&(scene->light), new);
	return (E_SUCCESS);
}

int				fill_light(char **file, t_scene *scene)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	ret = 0;
	scene->light = NULL;
	while (ft_strcmp(file[i], "lights"))
		i++;
	j = count_elem(&(file[i])) + i;
	while (i < j)
	{
		if (!ft_strcmp(file[i], "light"))
			if ((ret = fill_lux(file, scene, &i)) < 0)
				return (ret);
		i++;
	}
	if (scene->light->lux <= 0)
		return (ERR_FILL_LIGHT);
	return (E_SUCCESS);
}
