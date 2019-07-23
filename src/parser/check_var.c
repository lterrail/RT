/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:57:52 by lterrail          #+#    #+#             */
/*   Updated: 2019/06/18 16:09:05 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	check_var(char *line)
{
	int		i;
	int		j;
	char	**var;

	i = 0;
	j = -1;
	while (line[i] && line[i] != ':')
		i++;
	if (!ft_strncmp(line, "type", i) || !ft_strncmp(line, "path", i)
		|| !ft_strncmp(line, "texture", i) || !ft_strncmp(line, "shader", i))
		return (E_SUCCESS);
	if (!(var = ft_strsplit(line + i + 1, ';')))
		return (E_ERROR);
	while (var[++j])
	{
		if (!is_number(var[j]))
		{
			free_tab(var);
			return (E_ERROR);
		}
	}
	free_tab(var);
	if (j > 3)
		return (E_ERROR);
	return (E_SUCCESS);
}
