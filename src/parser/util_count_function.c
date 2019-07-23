/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_count_function.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lterrail <lterrail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 15:45:01 by lterrail          #+#    #+#             */
/*   Updated: 2019/06/12 15:46:08 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	count_line(char **file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	return (i);
}

int	count_elem(char **file)
{
	int	bracket;
	int	i;

	i = 1;
	bracket = 0;
	if (!ft_strcmp(file[i], "{"))
		bracket++;
	while (file[++i] && bracket > 0)
	{
		if (!ft_strcmp(file[i], "{"))
			bracket++;
		else if (!ft_strcmp(file[i], "}"))
			bracket--;
	}
	return (bracket == 0 && i > 1) ? i - 1 : -1;
}
