/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 16:39:03 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/08 11:23:11 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	overf;

	sign = 0;
	result = 0;
	overf = -1;
	while (*str == '\n' || *str == '\t' || *str == '\v' || *str == '\f'
			|| *str == '\r' || *str == ' ')
		str++;
	if (*str == '-')
		sign++;
	if (*str == '+' || *str == '-')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		if (++overf > 18 && sign == 0)
			return (-1);
		else if (overf > 19 && sign == 1)
			return (0);
		result = *str - '0' + result * 10;
		str++;
	}
	return (sign > 0) ? -result : result;
}
