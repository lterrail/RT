/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: temehenn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 08:49:44 by temehenn          #+#    #+#             */
/*   Updated: 2018/11/08 11:25:32 by temehenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		fill_nb(int n, char **nb)
{
	long long int	a;

	a = n;
	if (a < 0)
	{
		**nb = '-';
		(*nb)++;
		a = -a;
	}
	if (a >= 10)
		fill_nb((a / 10), nb);
	**nb = a % 10 + '0';
	(*nb)++;
}

static size_t	size(int nb)
{
	size_t			size;
	long long int	a;

	a = nb;
	size = 1;
	if (a < 0)
	{
		size++;
		a = -a;
	}
	while (a >= 10)
	{
		size++;
		a = a / 10;
	}
	return (size);
}

char			*ft_itoa(int n)
{
	char		*nb;
	char		*begin;

	nb = NULL;
	begin = NULL;
	if (!(nb = ft_strnew(size(n))))
		return (NULL);
	begin = nb;
	fill_nb(n, &nb);
	return (begin);
}
