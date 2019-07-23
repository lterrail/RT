/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mesh.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:01:32 by lterrail          #+#    #+#             */
/*   Updated: 2019/07/01 13:04:48 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
# define malloc(...) NULL
static int		fill_position(char **tab, int pos[4], int tot_line)
{
	int		i;

	i = 0;
	pos[0] = 0;
	pos[1] = 0;
	pos[2] = 0;
	while (tab[i] && ft_strncmp(tab[i], "v ", 2))
		i++;
	pos[0] = i;
	while (tab[i] && !ft_strncmp(tab[i], "v ", 2))
		i++;
	pos[1] = i;
	while (tab[i] && ft_strncmp(tab[i], "f ", 2))
		i++;
	pos[2] = i;
	if (pos[0] == tot_line || pos[1] == tot_line || pos[2] < pos[1])
		return (E_ERROR);
	return (E_SUCCESS);
}

static int		create_mesh_list(t_obj *obj, char **tab, int pos[4], int *id)
{
	t_obj	*new;
	int		ret[3];

	if (!(new = malloc(sizeof(t_obj))))
		return (0);
	ft_memcpy(new, obj, sizeof(t_obj));
	new->next = NULL;
	new->path = NULL;
	new->id = *id;
	pos[3] = 1;
	ret[0] = fill_mesh_value(tab, new->mesh.v0, pos);
	pos[3]++;
	ret[1] = fill_mesh_value(tab, new->mesh.v1, pos);
	pos[3]++;
	ret[2] = fill_mesh_value(tab, new->mesh.v2, pos);
	if (!ret[0] || !ret[1] || !ret[2])
	{
		free(new);
		return (E_ERROR);
	}
	obj->down == NULL ? obj->down = new : add_obj(&(obj->down), new);
	return (E_SUCCESS);
}

static int		init_mesh(t_obj *obj, char **tab, int tot_line, int *id)
{
	int		pos[4];

	init_transform(&obj->t, obj->pos, obj->dir);
	if (!fill_position(tab, pos, tot_line))
		return (E_ERROR);
	while (pos[2] < tot_line)
	{
		if (!create_mesh_list(obj, tab, pos, id))
			return (E_ERROR);
		(*id)++;
		pos[2]++;
	}
	return (E_SUCCESS);
}

static int		read_obj_file(t_obj *obj, int fd, char **tab, int *id)
{
	int		i;
	char	*line;

	i = 0;
	if ((fd = open(obj->path, O_RDONLY)) == -1)
		return (OPEN_OBJ_FILE_FAILED);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(tab[i++] = ft_strtrim(line)))
		{
			free(line);
			close(fd);
			free_tab(tab);
			return (FAILED_TO_MALLOC);
		}
		free(line);
	}
	close(fd);
	tab[i] = NULL;
	if (!init_mesh(obj, tab, i, id))
	{
		free_tab(tab);
		return (ERR_MESH);
	}
	return (E_SUCCESS);
}

int				check_mesh(t_obj *obj, int *id)
{
	int		fd;
	int		res;
	char	**tab;
	char	*line;
	int		tot_line;

	tot_line = 0;
	if ((fd = open(obj->path, O_RDONLY)) == -1
		|| ft_strcmp(".obj", obj->path + ft_strlen(obj->path) - 4) != 0)
		return (OPEN_OBJ_FILE_FAILED);
	while (get_next_line(fd, &line) > 0)
	{
		tot_line++;
		free(line);
	}
	close(fd);
	if (tot_line < 2 || tot_line > MAX_LINE)
		return (OBJ_FILE_TOO_BIG);
	if (!(tab = (char **)malloc(sizeof(char *) * (tot_line + 1))))
		return (FAILED_TO_MALLOC);
	if ((res = read_obj_file(obj, fd, tab, id)) < 0)
		return (res);
	free_tab(tab);
	return (E_SUCCESS);
}
