/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_is_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <temehenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 18:56:07 by temehenn          #+#    #+#             */
/*   Updated: 2019/06/18 17:44:59 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	is_token(char *line, char *token)
{
	int	i;

	i = 0;
	if (!check_semicolon(line))
		return (E_ERROR);
	while (line[i] && line[i] != ':')
		i++;
	if (ft_strncmp(line, token, i) || !line[i])
		return (E_ERROR);
	return (E_SUCCESS);
}

int	is_valid_vector(char **split)
{
	int	count;

	count = 0;
	while (split[count])
		count++;
	if (count != 3)
		return (E_ERROR);
	return (E_SUCCESS);
}

int	is_number(char *str)
{
	int	i;
	int	point;

	i = 0;
	point = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
			point++;
		if (str[i] != '.' && !ft_isdigit(str[i]))
			return (E_ERROR);
		if (str[i] == '.' && !str[i + 1])
			return (E_ERROR);
		i++;
	}
	return (point > 1) ? E_ERROR : E_SUCCESS;
}
