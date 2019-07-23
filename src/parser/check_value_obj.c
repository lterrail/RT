/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_value_obj.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 17:38:43 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/18 16:35:02 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		check_quadric(t_obj *obj)
{
	if (obj->albedo < 0 || obj->albedo > 1)
		return (E_ERROR);
	if (obj->shine > 1 || obj->shine < 0 || obj->p_spec < 0)
		return (E_ERROR);
	return (E_SUCCESS);
}

int		check_values(t_obj *obj)
{
	int	ret;

	ret = 0;
	if (obj->e_type == QUADRIC)
		ret = check_quadric(obj);
	else if (obj->e_type == MESH)
		ret = 1;
	else if (obj->e_type == TORE)
		ret = 1;
	else if (obj->e_type == CUBE)
		ret = 1;
	return (ret) ? E_SUCCESS : E_ERROR;
}
