/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 08:49:06 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/14 09:51:16 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_str(char **rest, char **line, int ret)
{
	char		*end;
	size_t		size;

	if ((end = ft_strchr(*rest, '\n')))
	{
		size = ft_strlen(end + 1);
		*line = *rest;
		*end = '\0';
		if (size)
		{
			if (!(*rest = ft_strsub(end + 1, 0, size)))
				return (-1);
		}
		else
			*rest = NULL;
		return (1);
	}
	else if (*rest && !ret)
	{
		*line = *rest;
		*rest = NULL;
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	char		buff[BUFF_SIZE + 1];
	int			ret;
	static char	*rest = NULL;
	int			check;
	char		*tmp;

	if (fd < 0 || !line)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		tmp = rest;
		if (!(rest = ft_strjoin(rest, buff)))
			return (-1);
		free(tmp);
		if ((check = check_str(&rest, line, ret)) == 1)
			return (1);
		else if (check == -1)
			return (-1);
	}
	if (ret == -1)
		return (-1);
	if (rest)
		return (check_str(&rest, line, ret));
	return (0);
}
