/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:58:33 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/27 13:59:22 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		rec_file(char *file_name, t_all *all)
{
	int		fd;
	char	*line;
	int		number;

	number = 0;
	if ((fd = open(file_name, O_RDONLY)) == -1
		|| ft_strcmp(".rt", file_name + ft_strlen(file_name) - 3) != 0)
		return (OPEN_RT_FILE_FAILED);
	while (get_next_line(fd, &line) > 0)
	{
		number++;
		free(line);
	}
	close(fd);
	if (number < 5 || number > 1000000)
		return (RT_FILE_TOO_BIG);
	if (!(all->file = malloc(sizeof(char *) * (number + 1))))
		return (FAILED_TO_MALLOC);
	return (E_SUCCESS);
}

int				read_file(char *file_name, t_all *all)
{
	int		fd;
	char	*line;
	int		i;
	int		ret;

	i = 0;
	if ((ret = rec_file(file_name, all)) < 0)
		return (ret);
	if ((fd = open(file_name, O_RDONLY)) == -1)
		return (OPEN_RT_FILE_FAILED);
	while (get_next_line(fd, &line) > 0)
	{
		if (!(all->file[i++] = ft_strtrim(line)))
		{
			close(fd);
			free(line);
			return (FAILED_TO_MALLOC);
		}
		free(line);
	}
	close(fd);
	all->file[i] = NULL;
	if ((ret = check_scene(all->file)) < 0)
		return (ret);
	return (E_SUCCESS);
}
