/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcottet <fcottet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 16:12:09 by fcottet           #+#    #+#             */
/*   Updated: 2019/06/13 15:46:38 by lterrail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	print_bar2(int test)
{
	if (test >= 50 && test <= 59)
		write(1, "\033[1;32m", 8);
	if (test >= 60 && test <= 69)
		write(1, "\033[0;33m", 8);
	if (test >= 70 && test <= 79)
		write(1, "\033[1;33m", 8);
	if (test >= 80 && test <= 89)
		write(1, "\033[1;31m", 8);
	if (test >= 90 && test <= 100)
		write(1, "\033[0;31m", 8);
}

void		print_bar(char c, t_bar bar)
{
	static int	test;

	if (bar.dl % (bar.dlmax / 100) != 0)
		return ;
	if (!test)
		test = 0;
	if (test >= 0 && test <= 9)
		write(1, "\033[0;34m", 8);
	if (test >= 10 && test <= 19)
		write(1, "\033[1;34m", 8);
	if (test >= 20 && test <= 29)
		write(1, "\033[0;36m", 8);
	if (test >= 30 && test <= 39)
		write(1, "\033[1;36m", 8);
	if (test >= 40 && test <= 49)
		write(1, "\033[0;32m", 8);
	print_bar2(test);
	write(1, &c, 1);
	write(1, "\033[0m", 5);
	test++;
}
